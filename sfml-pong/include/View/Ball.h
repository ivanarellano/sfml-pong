#pragma once
#include "Sound.h"
#include "Tickable.h"
#include "Visibility.h"
#include "Paddle.h"
#include <SFML\Graphics\CircleShape.hpp>

namespace Pong
{
	class Ball : public sf::CircleShape, public Visibility, public Tickable
	{
	public:
		Ball(int top_bound = 0, int btm_bound = 0, float radius = 7);

		void tick(float delta_time) override;

		void serve(bool isFacingLeftPlayer);
		void increase_speed(float vel);
		void on_collision();
		void check_collision(const Paddle& p1, const Paddle& p2);
	private:
		const float k_min_velocity{ 220.f };
		const float k_max_velocity{ k_min_velocity * 2.5f };
		const float k_spring_force{ 1.25f  };

		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
		Sound m_bounce_sound;
		int m_top_y_bound;
		int m_btm_y_bound;
	};
}