#include "PacketTypes.h"

namespace Pong
{
	void stamp_packet(const PacketType& l_type, sf::Packet& l_packet)
	{
		l_packet << PacketID(l_type);
	}
}
