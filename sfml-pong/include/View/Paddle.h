#pragma once
#include "Actor.h"

namespace Pong
{
	class Paddle : public Actor
	{
	public:
		explicit Paddle(sf::Vector2f size = sf::Vector2f{ 16.f, 50.f })
			: Actor{ size }
			, m_move_up{ false }
			, m_move_down{ false }
		{
		}

		void update(float dt) override;

		void set_name(std::string name) { m_name = name; }
		void move_up(bool can_move_up) { m_move_up = can_move_up; }
		void move_down(bool can_move_down) { m_move_down = can_move_down; }

		const std::string& get_name() const { return m_name; }
	private:
		std::string m_name;
		float m_move_speed{ 375.f };
		bool m_move_up{ false };
		bool m_move_down{ false };
	};
}