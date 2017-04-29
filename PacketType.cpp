#include "PacketType.h"

void set_packet(const PacketType& type, sf::Packet& packet) 
{
	packet << PacketID(type);
}