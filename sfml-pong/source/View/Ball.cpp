#include "Ball.h"
#include "Vector2Math.h"
#include "Random.h"
#include <iostream>

namespace Pong
{
	Ball::Ball(int top_bound, int btm_bound, float radius) 
		: CircleShape{ radius }
		, m_top_y_bound{ top_bound }
		, m_btm_y_bound{ btm_bound }
	{
		m_bounce_sound.load(Sound::Asset::blip);
	}

	void Ball::serve(bool isFacingLeftPlayer)
	{
		m_acceleration.x = isFacingLeftPlayer ? -1.f : 1.f;
		m_acceleration.y = coin_toss() ? -1.f : 1.f;

		m_acceleration *= k_min_velocity;
	}

	void Ball::increase_speed(float vel)
	{
		if (std::abs(Vec2Math::mag(m_acceleration)) < k_max_velocity)
		{
			m_acceleration.x *= vel;
			m_acceleration.y *= vel;
		}
		else 
		{
			m_acceleration = Vec2Math::norm(m_acceleration) * k_max_velocity;
		}
	}

	void Ball::on_collision()
	{
		m_bounce_sound.play();
	}

	void Ball::check_collision(const Paddle& p1, const Paddle& p2)
	{
		const bool did_hit_p1{ getGlobalBounds().intersects(p1.getGlobalBounds()) };
		const bool did_hit_p2{ getGlobalBounds().intersects(p2.getGlobalBounds()) };

		if (did_hit_p1)
		{
			setPosition(p1.getPosition().x + getRadius() + p1.get_half_width() + 0.1f, getPosition().y);
		} 
		else if (did_hit_p2)
		{
			setPosition(p2.getPosition().x - getRadius() - p2.get_half_width() - 0.1f, getPosition().y);
		}

		if (did_hit_p1 || did_hit_p2)
		{
			m_acceleration.x *= -1.f;
			on_collision();
			increase_speed(k_spring_force);
		}
		else if (getPosition().y - getRadius() < m_top_y_bound || getPosition().y + getRadius() > m_btm_y_bound)
		{
			m_acceleration.y *= -1.f;
			on_collision();
		}
	}

	void Ball::tick(float delta_time)
	{
		m_velocity = m_acceleration * delta_time;
		move(m_velocity);
	}
}