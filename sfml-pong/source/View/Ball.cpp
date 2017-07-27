#include "Ball.h"
#include "Vector2Math.h"
#include "Random.h"
#include <iostream>

namespace Pong
{
	Ball::Ball(float radius) : m_shape{ radius }
	{
		m_bounce_sound.load(Sound::Asset::blip);
	}

	void Ball::serve(bool isFacingLeftPlayer)
	{
		m_acceleration.x = isFacingLeftPlayer ? -1.f : 1.f;
		m_acceleration.y = coin_toss() ? -1.f : 1.f;

		m_acceleration *= k_min_velocity;
	}

	void Ball::tick(float delta_time)
	{
		m_velocity = m_acceleration * delta_time;
		m_shape.move(m_velocity);
	}

	void Ball::increase_speed(float vel)
	{
		m_acceleration.x += vel;
		m_acceleration.y += vel;
	}

	void Ball::on_collision()
	{
		m_bounce_sound.play();
		increase_speed(k_spring_force);
	}
}