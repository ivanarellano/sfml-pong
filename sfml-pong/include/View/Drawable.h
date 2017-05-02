#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace Pong
{
	class Drawable
	{
	public:
		virtual ~Drawable() {}

		virtual void draw(sf::RenderTarget* target) = 0;
	};
}