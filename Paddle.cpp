#include "Paddle.h"

namespace Pong
{
	Paddle::Paddle() : Paddle { sf::Vector2f { 16.f, 50.f }, 375.f }
	{
	}

	void Paddle::update(float dt)
	{
		if (m_move_up)
		{
			move(0, -m_move_speed * dt);
		}
		else if (m_move_down)
		{
			move(0, m_move_speed * dt);
		}
	}
}