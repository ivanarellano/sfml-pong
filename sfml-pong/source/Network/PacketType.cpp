#include "PacketType.h"

void fill_packet(const PacketType& type, sf::Packet& packet) 
{
	packet << PacketID(type);
}