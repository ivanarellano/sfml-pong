#pragma once
#include "Actor.h"

namespace Pong
{
	class Paddle : public Actor
	{
	public:
		Paddle();

		explicit Paddle(sf::Vector2f size, float move_speed)
			: Actor{ size }
			, m_move_speed{ move_speed }
			, m_move_up{ false }
			, m_move_down{ false }
		{}

		void update(float dt) override;

		void move_up(bool can_move_up) { m_move_up = can_move_up; }
		void move_down(bool can_move_down) { m_move_down = can_move_down; }
	private:
		float m_move_speed;
		bool m_move_up;
		bool m_move_down;
	};
}