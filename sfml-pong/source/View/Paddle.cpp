#include "Paddle.h"

namespace Pong
{
	void Paddle::tick(float delta_time)
	{
		float speed{ m_move_speed * delta_time };
		if (m_move_up)
		{
			m_shape.move(0, -speed);
		}
		else if (m_move_down)
		{
			m_shape.move(0, speed);
		}
	}
}