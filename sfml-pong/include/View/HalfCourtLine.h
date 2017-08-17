#pragma once
#include "Visibility.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	/*
	* A half court line with a dashed line effect.
	*/
	struct HalfCourtLine : sf::Drawable
	{
		HalfCourtLine(sf::Vector2u screen_sz, 
			sf::Vector2i dash_sz = sf::Vector2i { 6, 20 }, int gap = 30);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		std::vector<sf::RectangleShape> m_notches;
	};
}