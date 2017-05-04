#pragma once
#include <SFML/System/Vector2.hpp>

namespace Pong
{
	class Movable
	{
	public:
		virtual ~Movable() {}

		virtual sf::Vector2f get_position() const = 0;
		virtual void set_position(float x, float y) = 0;
		virtual void move(float x, float y) = 0;
	};
}
