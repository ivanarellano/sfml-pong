#pragma once
#include "Tickable.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <string>

namespace Pong
{
	class Paddle : public sf::RectangleShape, public Tickable
	{
	public:
		Paddle(const std::string& name_tag, sf::Vector2f size = sf::Vector2f{ 16.f, 50.f })
			: RectangleShape{ size }
			, m_name{ name_tag }
		{
		}

		void tick(float delta_time) override;

		void set_name(std::string name) { m_name = name; }
		void move_up(bool can_move_up) { m_move_up = can_move_up; }
		void move_down(bool can_move_down) { m_move_down = can_move_down; }

		const std::string& get_name() const { return m_name; }

		float get_half_width() { return getSize().x / 2.f; }
		float get_half_height() { return getSize().y / 2.f; }
	private:
		std::string m_name;
		float m_move_speed{ 375.f };
		bool m_move_up{ false };
		bool m_move_down{ false };
	};
}