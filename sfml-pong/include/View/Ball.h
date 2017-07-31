#pragma once
#include "Sound.h"
#include "Tickable.h"
#include "Visibility.h"
#include <SFML\Graphics\CircleShape.hpp>

namespace Pong
{
	class Ball : public sf::CircleShape, public Visibility, public Tickable
	{
	public:
		explicit Ball(float radius = 7);

		void tick(float delta_time) override;

		void serve(bool isFacingLeftPlayer);
		void increase_speed(float vel);
		void on_collision();
	private:
		const float k_min_velocity{ 200.f };
		const float k_max_velocity{ k_min_velocity * 4.f };
		const float k_spring_force{ 1 };
		const float k_pi{ 3.14159f };

		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
		Sound m_bounce_sound;
		float ball_angle{ 0.f };
	};
}