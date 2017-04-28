#include "Server.h"

Pong::Server::Server(void(* handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*))
	: m_last_id {0}
	, m_running {false}
	, m_listen_thread {nullptr}
	, m_totasent {0}
	, m_total_received {0}
{
}

Pong::Server::~Server()
{
}

void Pong::Server::bind_timeout_handler(void(* handler)(const ClientID&))
{
}

bool Pong::Server::send(const ClientID& id, sf::Packet& packet)
{
}

bool Pong::Server::send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet)
{
}

void Pong::Server::broadcast(sf::Packet& packet, const ClientID& ignore)
{
}

void Pong::Server::listen()
{
}

void Pong::Server::update(const sf::Time& time)
{
}

ClientID Pong::Server::add_client(const sf::IpAddress& ip, const PortNumber& port)
{
}

ClientID Pong::Server::get_client_id(const sf::IpAddress& ip, const PortNumber& port)
{
}

bool Pong::Server::has_client(const ClientID& id)
{
}

bool Pong::Server::has_client(const sf::IpAddress& ip, const PortNumber& port)
{
}

bool Pong::Server::fill_client_info(const ClientID& id, ClientInfo& info)
{
}

bool Pong::Server::remove_client(const ClientID& id)
{
}

bool Pong::Server::remove_client(const sf::IpAddress& ip, const PortNumber& port)
{
}

void Pong::Server::disconnect_all()
{
}

bool Pong::Server::start()
{
}

bool Pong::Server::stop()
{
}

bool Pong::Server::is_running()
{
}

std::string Pong::Server::get_client_list()
{
}

sf::Mutex& Pong::Server::get_mutex()
{
}
>>>>>>> Stashed changes
