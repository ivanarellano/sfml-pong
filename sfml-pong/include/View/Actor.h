#pragma once
#include "View.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	struct Actor : View
	{
		explicit Actor(sf::Vector2f size) : m_rect { size } {}

		virtual void update(float dt) = 0;

		sf::FloatRect get_bounds() const override { return m_rect.getGlobalBounds(); }
		void draw(sf::RenderTarget* window) override { if (is_visible()) window->draw(get_shape()); }

		sf::Vector2f get_position() const override { return m_rect.getPosition(); }
		void set_position(float x, float y) override { m_rect.setPosition(x, y); }
		void move(float x, float y) override { m_rect.move(x, y); }		

		sf::RectangleShape get_shape() const { return m_rect; }
		sf::RectangleShape m_rect;
	private:
	};
}