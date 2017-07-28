#include "Paddle.h"

namespace Pong
{
	void Paddle::tick(float delta_time)
	{
		float speed{ m_move_speed * delta_time };
		if (m_move_up)
		{
			move(0, -speed);
		}
		else if (m_move_down)
		{
			move(0, speed);
		}
	}
}