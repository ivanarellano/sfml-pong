#pragma once
#include "PacketType.h"
#include "ClientInfo.h"
#include <functional>
#include <unordered_map>

#define HEARTBEAT_INTERVAL_MS 1000
#define HEARTBEAT_RETRIES 5

using Clients = std::unordered_map<ClientID, ClientInfo>;
class Server;
using PacketHandler = std::function<void(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*)>;
using TimeoutHandler = std::function<void(const ClientID&)>;

class Server
{
public:
	template <class T>
	Server(void(T::*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*), T* instance)
		: m_last_id { 0 }
		, m_running { false }
		, m_listen_thread { &Server::listen, this }
		, m_total_sent {0}
		, m_total_received {0}
	{
		m_packet_handler = std::bind(handler, instance, 
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
			std::placeholders::_4, std::placeholders::_5);
	}

	Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*));
	~Server();

	template<class T>
	void bind_timeout_handler(void(T::*handler)(const ClientID&), T* instance) 
	{
		m_timeout_handler = std::bind(handler, instance, std::placeholders::_1);
	}

	void bind_timeout_handler(void(*handler)(const ClientID&));

	bool send(const ClientID& id, sf::Packet& packet);
	bool send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet);
	void broadcast(sf::Packet& packet, const ClientID& ignore = static_cast<ClientID>(Network::NullID));

	void listen();
	void update(const sf::Time& time);

	ClientID add_client(const sf::IpAddress& ip, const PortNumber& port);
	ClientID get_client_id(const sf::IpAddress& ip, const PortNumber& port);
	bool has_client(const ClientID& id);
	bool has_client(const sf::IpAddress& ip, const PortNumber& port);
	bool fill_client_info(const ClientID& id, ClientInfo& info);
	bool remove_client(const ClientID& id);
	bool remove_client(const sf::IpAddress& ip, const PortNumber& port);

	void disconnect_all();
	bool start();
	bool stop();

	bool is_running() const;

	unsigned int get_client_count() const { return m_clients.size(); };
	std::string get_client_list();

	sf::Mutex& get_mutex();
private:
	ClientID m_last_id;

	sf::UdpSocket m_incoming;
	sf::UdpSocket m_outgoing;

	PacketHandler m_packet_handler;
	TimeoutHandler m_timeout_handler;

	Clients m_clients;
	sf::Time m_server_time;

	bool m_running;

	sf::Thread m_listen_thread;
	sf::Mutex m_mutex;

	size_t m_total_sent;
	size_t m_total_received;
};