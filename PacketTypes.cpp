#include "PacketTypes.h"

void set_packet(const PacketType& l_type, sf::Packet& l_packet) 
{
	l_packet << PacketID(l_type);
}