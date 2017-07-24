#pragma once
#include "Drawable.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	/*
	* A half court line with a dashed line effect.
	* The width and height represent the size of a single dash.
	*/
	class HalfCourtLine : public Drawable
	{
	public:
		HalfCourtLine();

		HalfCourtLine(sf::Vector2f size, float gap);

		void draw(sf::RenderTarget* target) override;
	private:
		float m_dash_width;
		float m_dash_height;
		std::vector<sf::RectangleShape> m_notches;
	};
}