#include "Server.h"
#include <iostream>

namespace Pong
{
	Server::Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*))
		: m_last_id{ 0 }
		, m_running{ false }
		, m_listen_thread{ &Server::listen, this }
		, m_total_sent{ 0 }
		, m_total_received{ 0 }
	{
		m_packet_handler = bind(handler,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
			std::placeholders::_4, std::placeholders::_5);
	}

	Server::~Server()
	{
		stop();
	}

	void Server::bind_timeout_handler(void(*handler)(const ClientID&))
	{
		m_timeout_handler = bind(handler, std::placeholders::_1);
	}

	bool Server::send(const ClientID& id, sf::Packet& packet)
	{
		sf::Lock lock{ m_mutex };

		auto itr = m_clients.find(id);
		if (itr == m_clients.end())
			return false;

		return send(itr->second.m_ip, itr->second.m_port, packet);
	}

	bool Server::send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet)
	{
		if (m_outgoing.send(packet, ip, port) != sf::Socket::Done)
		{
			std::cout << "Error sending a packet..." << std::endl;
			return false;
		}

		m_total_sent += packet.getDataSize();

		return true;
	}

	void Server::broadcast(sf::Packet& packet, const ClientID& ignore)
	{
		sf::Lock lock{ m_mutex };

		for (auto& itr : m_clients)
		{
			if (itr.first != ignore)
			{
				if (m_outgoing.send(packet, itr.second.m_ip, itr.second.m_port) != sf::Socket::Done)
				{
					std::cout << "Error broadcasting a packet to client: " << itr.first << std::endl;
					continue;
				}

				m_total_sent += packet.getDataSize();
			}
		}
	}

	void Server::listen()
	{
		sf::IpAddress ip;
		PortNumber port;
		sf::Packet packet;

		std::cout << "Beginning to listen..." << std::endl;

		while (m_running)
		{
			packet.clear();

			sf::Socket::Status status = m_incoming.receive(packet, ip, port);
			if (status != sf::Socket::Done)
			{
				if (m_running)
				{
					std::cout << "Error receiving a packet from: "
						<< ip << ":" << port << ". Code: "
						<< status << std::endl;
					continue;
				}

				std::cout << "Socket unbound." << std::endl;
				break;
			}

			m_total_received += packet.getDataSize();

			PacketID p_id;
			if (!(packet >> p_id))
			{
				std::cout << "Invalid packet received: unable to extract id." << std::endl;
				continue;
			}

			PacketType id = static_cast<PacketType>(p_id);
			if (id < PacketType::Disconnect || id >= PacketType::OutOfBounds)
			{
				std::cout << "Invalid packet received: id is out of bounds." << std::endl;
				continue;
			}

			if (id == PacketType::Heartbeat)
			{
				sf::Lock lock{ m_mutex };

				for (auto& itr : m_clients)
				{
					if (itr.second.m_ip != ip || itr.second.m_port != port)
						continue;

					if (!itr.second.m_heartbeat_waiting)
					{
						std::cout << "Invalid heartbeat packet received!"
							<< std::endl;
						break;
					}

					itr.second.m_latency = m_server_time.asMilliseconds() -
						itr.second.m_heartbeat_sent.asMilliseconds();
					itr.second.m_last_heartbeat = m_server_time;
					itr.second.m_heartbeat_waiting = false;
					itr.second.m_heartbeat_retry = 0;
					break;
				}
			}
			else if (m_packet_handler)
			{
				m_packet_handler(ip, port, static_cast<PacketID>(id), packet, this);
			}
		}
	}

	void Server::update(const sf::Time& time)
	{
		m_server_time += time;

		if (m_server_time.asMilliseconds() < 0)
		{
			constexpr sf::Int32 max_timestamp = static_cast<sf::Int32>(Network::HighestTimestamp);

			m_server_time -= sf::milliseconds(max_timestamp);
			sf::Lock lock{ m_mutex };

			for (auto& itr : m_clients)
			{
				itr.second.m_last_heartbeat = sf::milliseconds(abs(
					itr.second.m_last_heartbeat.asMilliseconds() - max_timestamp
				));
			}
		}

		sf::Lock lock{ m_mutex };

		// Set heartbeats for known clients
		for (auto itr = m_clients.begin(); itr != m_clients.end();)
		{
			sf::Int32 elapsed = m_server_time.asMilliseconds() -
				itr->second.m_last_heartbeat.asMilliseconds();

			if (elapsed >= HEARTBEAT_INTERVAL_MS)
			{
				constexpr sf::Int32 timeout = static_cast<sf::Int32>(Network::ClientTimeout);

				if (elapsed >= timeout || itr->second.m_heartbeat_retry > HEARTBEAT_RETRIES)
				{
					std::cout << "Client " << itr->first << " has timed out." << std::endl;

					if (m_timeout_handler)
						m_timeout_handler(itr->first);

					itr = m_clients.erase(itr);
				}

				if (!itr->second.m_heartbeat_waiting || elapsed >= HEARTBEAT_INTERVAL_MS * (itr->second.m_heartbeat_retry + 1))
				{
					// 1) Client is not waiting for reply. 2) It's time to send another heartbeat

					if (itr->second.m_heartbeat_retry >= 3)
					{
						std::cout << "Re-try(" << itr->second.m_heartbeat_retry
							<< ") heartbeat for client "
							<< itr->first << std::endl;
					}

					sf::Packet p;
					set_packet(PacketType::Heartbeat, p);

					p << m_server_time.asMilliseconds();
					send(itr->first, p);

					if (itr->second.m_heartbeat_retry == 0)
						itr->second.m_heartbeat_sent = m_server_time;

					itr->second.m_heartbeat_waiting = true;
					itr->second.m_heartbeat_retry += 1;

					m_total_sent += p.getDataSize();
				}
			}

			++itr;
		}
	}

	ClientID Server::add_client(const sf::IpAddress& ip, const PortNumber& port)
	{
		sf::Lock lock{ m_mutex };

		for (auto& itr : m_clients)
		{
			if (itr.second.m_ip == ip && itr.second.m_port == port)
				return ClientID(Network::NullID);
		}

		ClientID id{ m_last_id };
		ClientInfo info{ ip, port, m_server_time };

		m_clients.insert(std::make_pair(id, info));
		++m_last_id;

		return id;
	}

	ClientID Server::get_client_id(const sf::IpAddress& ip, const PortNumber& port)
	{
		sf::Lock lock{ m_mutex };

		for (auto& itr : m_clients)
		{
			if (itr.second.m_ip == ip && itr.second.m_port == port)
				return itr.first;
		}

		return ClientID(Network::NullID);
	}

	bool Server::has_client(const ClientID& id)
	{
		return m_clients.find(id) != m_clients.end();
	}

	bool Server::has_client(const sf::IpAddress& ip, const PortNumber& port)
	{
		return get_client_id(ip, port) != ClientID(Network::NullID);
	}

	bool Server::fill_client_info(const ClientID& id, ClientInfo& info)
	{
		sf::Lock lock{ m_mutex };

		for (auto& itr : m_clients)
		{
			if (itr.first == id)
			{
				info = itr.second;
				return true;
			}
		}

		return false;
	}

	bool Server::remove_client(const ClientID& id)
	{
		sf::Lock lock{ m_mutex };

		auto itr = m_clients.find(id);
		if (itr == m_clients.end())
			return false;

		sf::Packet p;
		set_packet(PacketType::Disconnect, p);
		send(id, p);

		m_clients.erase(itr);

		return true;
	}

	bool Server::remove_client(const sf::IpAddress& ip, const PortNumber& port)
	{
		ClientID id{ get_client_id(ip, port) };

		if (id != ClientID(Network::NullID))
			return remove_client(id);

		return false;
	}

	void Server::disconnect_all()
	{
		if (!m_running)
			return;

		sf::Packet p;
		set_packet(PacketType::Disconnect, p);
		broadcast(p);

		sf::Lock lock{ m_mutex };
		m_clients.clear();
	}

	bool Server::start()
	{
		if (m_running)
			return false;

		// Check for failure when binding incoming socket to port
		if (m_incoming.bind(static_cast<unsigned short>(Network::ServerPort)) != sf::Socket::Done)
			return false;

		m_outgoing.bind(sf::Socket::AnyPort);

		std::cout << "Incoming port: "
			<< m_incoming.getLocalPort() << ". Outgoing port: "
			<< m_outgoing.getLocalPort() << std::endl;

		m_listen_thread.launch();
		m_running = true;

		return true;
	}

	bool Server::stop()
	{
		if (!m_running)
			return false;

		disconnect_all();

		m_running = false;
		m_incoming.unbind();

		return true;
	}

	bool Server::is_running() const
	{
		return m_running;
	}

	std::string Server::get_client_list()
	{
		std::string output;
		sf::Lock lock{ m_mutex };

		int i = 0;
		for (auto& itr : m_clients)
		{
			output += itr.second.m_ip.toString();

			if (i > 0)
				output += ", ";

			++i;
		}

		return output;
	}

	sf::Mutex& Server::get_mutex()
	{
		return m_mutex;
	}
}