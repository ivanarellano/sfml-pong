#include "Client.h"
#include <SFML\System\Clock.hpp>
#include <iostream>

namespace Pong
{
	void handle_packet(const PacketID& id, sf::Packet& packet, Client* client)
	{
		auto type = static_cast<PacketType>(id);

		if (PacketType::Message == type)
		{
			std::string message;
			packet >> message;

			std::cout << message << std::endl;
		}
		else if (PacketType::Disconnect == type)
		{
			client->disconnect();
		}
	}

	Client::Client()
		: m_server_port{ 0 }
		, m_connected{ false }
		, m_listen_thread{ &Client::listen, this }
	{
	}

	Client::~Client()
	{
		m_socket.unbind();
	}

	bool Client::connect()
	{
		if (m_connected)
			return false;

		m_socket.bind(sf::Socket::AnyPort);
		std::cout << "Bound client to port: " << m_socket.getLocalPort() << std::endl;

		sf::Packet p;
		fill_packet(PacketType::Connect, p);
		p << m_player_name;

		if (m_socket.send(p, m_server_ip, m_server_port) != sf::Socket::Done)
		{
			m_socket.unbind();
			return false;
		}

		m_socket.setBlocking(false);
		p.clear();

		sf::IpAddress recvIP;
		PortNumber recvPORT;
		sf::Clock timer;

		timer.restart();

		std::cout << "Attempting to connect to: " << m_server_ip << ":"
			<< m_server_port << std::endl;

		while (timer.getElapsedTime().asMilliseconds() < CONNECT_TIMEOUT_MS)
		{
			sf::Socket::Status s = m_socket.receive(p, recvIP, recvPORT);
			if (s != sf::Socket::Done)
				continue;

			if (recvIP != m_server_ip)
				continue;

			PacketID id;
			if (!(p >> id))
				break;

			if (static_cast<PacketType>(id) != PacketType::Connect)
				continue;

			m_packet_handler(id, p, this);
			m_connected = true;
			m_socket.setBlocking(true);
			m_last_heartbeat = m_server_time;
			m_listen_thread.launch();

			return true;
		}

		std::cout << "Connection attempt failed! Server info: "
			<< m_server_ip << ":" << m_server_port << std::endl;

		m_socket.unbind();
		m_socket.setBlocking(true);

		return false;
	}

	bool Client::disconnect()
	{
		if (!m_connected)
			return false;

		sf::Packet p;
		fill_packet(PacketType::Disconnect, p);

		sf::Socket::Status status = m_socket.send(p, m_server_ip, m_server_port);

		m_connected = false;
		m_socket.unbind(); // Unbind to close the listening thread.

		return status != sf::Socket::Done ? false : true;
	}

	void Client::listen()
	{
		sf::Packet packet;
		sf::IpAddress recvIP;
		PortNumber recvPORT;

		while (m_connected)
		{
			packet.clear();
			sf::Socket::Status status = m_socket.receive(packet, recvIP, recvPORT);

			if (status != sf::Socket::Done)
			{
				if (m_connected) {
					std::cout << "Failed receiving a packet from "
						<< recvIP << ":" << recvPORT << ". Status: "
						<< status << std::endl;
					continue;
				}
				else {
					std::cout << "Socket unbound." << std::endl;
				}
				break;
			}

			if (recvIP != m_server_ip)
			{
				// Ignore packets not sent from the server.
				continue;
			}

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
				sf::Packet p;
				fill_packet(PacketType::Heartbeat, p);

				if (m_socket.send(p, m_server_ip, m_server_port) != sf::Socket::Done)
					std::cout << "Failed sending a heartbeat!" << std::endl;

				sf::Int32 timestamp;
				packet >> timestamp;
				set_time(sf::milliseconds(timestamp));

				m_last_heartbeat = m_server_time;
			}
			else if (m_packet_handler)
			{
				m_packet_handler(static_cast<PacketID>(id), packet, this);
			}
		}
	}

	bool Client::send(sf::Packet& packet)
	{
		if (!m_connected)
			return false;

		if (m_socket.send(packet, m_server_ip, m_server_port) != sf::Socket::Done)
			return false;

		return true;
	}

	const sf::Time& Client::get_time() const
	{
		return m_server_time;
	}

	const sf::Time& Client::get_last_heartbeat() const
	{
		return m_last_heartbeat;
	}

	void Client::set_time(const sf::Time& time)
	{
		m_server_time = time;
	}

	void Client::set_server_information(const sf::IpAddress& ip, const PortNumber& port)
	{
		m_server_ip = ip;
		m_server_port = port;
	}

	void Client::setup(void(*handler)(const PacketID&, sf::Packet&, Client*))
	{
		m_packet_handler = std::bind(handler,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}

	void Client::unregister_packet_handler()
	{
		m_packet_handler = nullptr;
	}

	void Client::update(const sf::Time& time)
	{
		if (!m_connected)
			return;

		m_server_time += time;

		if (m_server_time.asMilliseconds() < 0)
		{
			m_server_time -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
			m_last_heartbeat = m_server_time;
			return;
		}

		if (m_server_time.asMilliseconds() - m_last_heartbeat.asMilliseconds() >=
			sf::Int32(Network::ClientTimeout))
		{
			std::cout << "Server connection timed out!" << std::endl;
			disconnect();
		}
	}

	bool Client::is_connected() const
	{
		return m_connected;
	}

	void Client::set_player_name(const std::string& name)
	{
		m_player_name = name;
	}

	sf::Mutex& Client::get_mutex()
	{
		return m_mutex;
	}
}