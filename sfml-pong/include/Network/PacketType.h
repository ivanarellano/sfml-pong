#pragma once
#include <SFML/Network/Packet.hpp>

using PacketID = sf::Int8;

enum class PacketType 
{
	Disconnect = -1, Connect, Heartbeat, Snapshot, 
	PlayerUpdate, Message, OutOfBounds
};

void set_packet(const PacketType& type, sf::Packet& packet);