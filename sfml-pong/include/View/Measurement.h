#pragma once
#include "SFML/Graphics/Rect.hpp"

namespace Pong
{
	class Measurement
	{
	public:
		virtual ~Measurement() {}

		virtual sf::FloatRect get_bounds() const = 0;
	};
}