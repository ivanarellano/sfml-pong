#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace Pong
{
	class Drawable
	{
	public:
		enum class Visibility
		{
			Visible, Gone
		};

		virtual ~Drawable() {}

		virtual void draw(sf::RenderWindow* window) = 0;
	};
}