#include "Paddle.h"

namespace Pong
{
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