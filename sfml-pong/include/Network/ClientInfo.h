#pragma once
#include "NetworkDefinitions.h"
#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

struct ClientInfo {
	ClientInfo(const sf::IpAddress& ip, const PortNumber& port, const sf::Time& heartbeat)
		: m_ip { ip }
		, m_port { port }
		, m_last_heartbeat { heartbeat }
		, m_heartbeat_waiting { false }
		, m_heartbeat_retry { 0 }
		, m_latency { 0 }
	{}

	ClientInfo& operator=(const ClientInfo& info) {
		m_ip = info.m_ip;
		m_port = info.m_port;
		m_last_heartbeat = info.m_last_heartbeat;
		m_heartbeat_sent = info.m_heartbeat_sent;
		m_heartbeat_waiting = info.m_heartbeat_waiting;
		m_heartbeat_retry = info.m_heartbeat_retry;
		m_latency = info.m_latency;
		return *this;
	}

	sf::IpAddress m_ip;
	PortNumber m_port;
	sf::Time m_last_heartbeat;
	sf::Time m_heartbeat_sent;
	bool m_heartbeat_waiting;
	unsigned short m_heartbeat_retry;
	unsigned int m_latency;
};
