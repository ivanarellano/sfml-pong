#pragma once
#include "PacketTypes.h"
#include "NetworkDefinitions.h"
#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>
#include <functional>

namespace Pong
{

#define CONNECT_TIMEOUT_MS 5000

class Client;

using PacketHandler = std::function<void(const PacketID&, sf::Packet&, Client*)>;

class Client {
public:
	Client();
	~Client();

	bool connect();
	bool disconnect();
	void listen();
	bool send(sf::Packet& packet);
	const sf::Time& get_time() const;
	const sf::Time& get_last_heartbeat() const;
	void set_time(const sf::Time& time);
	void set_server_information(const sf::IpAddress& ip, const PortNumber& port);

	template<class T>
	void setup(void(T::*handler) (const PacketID&, sf::Packet&, Client*), T* instance)
	{
		m_packet_handler = std::bind(handler, instance,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}

	void setup(void(*handler) (const PacketID&, sf::Packet&, Client*));
	void unregister_packet_handler();
	void update(const sf::Time& time);
	bool is_connected() const;
	void set_player_name(const std::string& name);

	sf::Mutex& get_mutex();
private:
	std::string m_player_name;

	sf::UdpSocket m_socket;
	sf::IpAddress m_server_ip;
	PortNumber m_server_port;
	PacketHandler m_packet_handler;
	bool m_connected;
	sf::Time m_server_time;
	sf::Time m_last_heartbeat;

	sf::Thread m_listen_thread;
	sf::Mutex m_mutex;
};

}