#include "Ball.h"

namespace Pong
{
	Ball::Ball(sf::Vector2f size) : Actor{ size }
	{
		m_bounce_sound.load(Sound::Asset::blip);
		initialize();
	}

	void Ball::update(float dt)
	{
		m_velocity *= dt;
		move(m_velocity.x, m_velocity.y);
	}

	void Ball::increase_velocity(float vel)
	{
		m_velocity.x += vel;
		m_velocity.y += vel;

		//if (new_vel < k_max_velocity)
		//{
		//	m_velocity = new_vel;
		//}
		//else
		//{
		//	m_velocity = k_max_velocity;
		//}
	}

	void Ball::initialize()
	{
		m_velocity.x = k_min_velocity; 
		m_velocity.y = k_min_velocity;
	}

	void Ball::on_collision()
	{
		m_bounce_sound.play();
		increase_velocity(k_spring_force);
	}
}