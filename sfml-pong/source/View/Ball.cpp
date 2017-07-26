#include "Ball.h"
#include "Vector2Math.h"
#include "Random.h"
#include <iostream>

namespace Pong
{
	Ball::Ball(sf::Vector2f size) : Actor{ size }
	{
		m_bounce_sound.load(Sound::Asset::blip);
	}

	void Ball::serve(bool isFacingLeftPlayer)
	{
		m_acceleration.x = isFacingLeftPlayer ? -1.f : 1.f;
		m_acceleration.y = coin_toss() ? -1.f : 1.f;

		m_acceleration *= k_min_velocity;
	}

	void Ball::update(float dt)
	{
		m_velocity = m_acceleration * dt;
		m_rect.move(m_velocity);
	}

	void Ball::increase_velocity(float vel)
	{
		m_acceleration.x += vel;
		m_acceleration.y += vel;

		std::cout << "Increased velocity  x: " << m_acceleration.x 
			<< ", y:" << m_acceleration.y << std::endl;
	}

	void Ball::on_collision()
	{
		m_bounce_sound.play();
		increase_velocity(k_spring_force);
	}
}