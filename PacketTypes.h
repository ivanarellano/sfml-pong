#pragma once
#include <SFML/Network/Packet.hpp>

namespace Pong
{
	using PacketID = sf::Int8;

	enum class PacketType
	{
		Disconnect = -1, Connect, Heartbeat, Snapshot, PlayerUpdate, Message,
	};

	void stamp_packet(const PacketType& l_type, sf::Packet& l_packet);
}