#pragma once
#include "Drawable.h"
#include "Measurement.h"
#include "Movable.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace Pong
{
	struct Actor : Drawable, Measurement, Movable
	{
		explicit Actor(sf::Vector2f size)
			: m_rect { size }
			, m_visibility { Visibility::Visible }
		{}

		virtual void update(float dt) = 0;

		const std::string& get_name() const { return m_name; }
		void set_name(std::string name) { m_name = name; }

		float get_width() const override { return m_rect.getSize().x; }
		float get_height() const override { return m_rect.getSize().y; }

		void draw(sf::RenderWindow* window) override { if (is_visible()) window->draw(get_shape()); }
		void set_position(float x, float y) override { m_rect.setPosition(x, y); }
		void move(float x, float y) override { m_rect.move(x, y); }

		sf::RectangleShape get_shape() const { return m_rect; }
		bool is_visible() const { return m_visibility == Visibility::Visible ? true : false; }

		void set_visibility(Visibility vis) { m_visibility = vis; }
	private:
		sf::RectangleShape m_rect;
		Visibility m_visibility;
		std::string m_name;
	};
}