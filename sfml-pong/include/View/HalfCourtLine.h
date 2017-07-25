#pragma once
#include "Drawable.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	/*
	* A half court line with a dashed line effect.
	*/
	class HalfCourtLine : public Drawable
	{
	public:
		HalfCourtLine(sf::Vector2u screen_sz,
			sf::Vector2i dash_sz = sf::Vector2i { 6, 20 }, int gap = 30);

		void draw(sf::RenderTarget* target) override;
	private:
		std::vector<sf::RectangleShape> m_notches;
	};
}