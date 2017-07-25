#include "Ball.h"

namespace Pong
{
	Ball::Ball(sf::Vector2f size) : Actor{ size }
	{
		m_bounce_sound.load(Sound::Asset::blip);
	}

	void Ball::update(float dt)
	{
		const float time_adjusted_speed = m_velocity * dt;
		switch (m_direction)
		{
		case Direction::NW:
			move(-time_adjusted_speed, -time_adjusted_speed);
			break;
		case Direction::NE:
			move(time_adjusted_speed, -time_adjusted_speed);
			break;
		case Direction::SW:
			move(-time_adjusted_speed, time_adjusted_speed);
			break;
		case Direction::SE:
			move(time_adjusted_speed, time_adjusted_speed);
			break;
		case Direction::None:
			break;
		}
	}

	void Ball::increase_velocity(float vel)
	{
		float new_vel = m_velocity + vel;

		if (new_vel < k_max_velocity)
		{
			m_velocity = new_vel;
		}
		else
		{
			m_velocity = k_max_velocity;
		}
	}

	void Ball::reflect_on_court()
	{
		m_bounce_sound.play();

		switch (m_direction)
		{
		case Direction::NW:
			m_direction = Direction::SW;
			break;
		case Direction::NE:
			m_direction = Direction::SE;
			break;
		case Direction::SW:
			m_direction = Direction::NW;
			break;
		case Direction::SE:
			m_direction = Direction::NE;
			break;
		default:
			m_direction = Direction::None;
		}
	}

	void Ball::reflect_on_paddle()
	{
		m_bounce_sound.play();
		increase_velocity(k_spring_force);

		switch (m_direction)
		{
		case Direction::NW:
			m_direction = Direction::NE;
			break;
		case Direction::NE:
			m_direction = Direction::NW;
			break;
		case Direction::SW:
			m_direction = Direction::SE;
			break;
		case Direction::SE:
			m_direction = Direction::SW;
			break;
		default:
			m_direction = Direction::None;
		}
	}
}