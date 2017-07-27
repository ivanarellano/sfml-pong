#pragma once
#include "Sound.h"
#include "View.h"
#include <SFML\Graphics\CircleShape.hpp>

namespace Pong
{
	class Ball : public View, public Tickable
	{
	public:
		explicit Ball(float radius = 10);

		void tick(float delta_time) override;

		void serve(bool isFacingLeftPlayer);
		void increase_speed(float vel);
		void on_collision();

		sf::CircleShape get_shape() { return m_shape; }
	private:
		const float k_min_velocity{ 100.f };
		const float k_max_velocity{ 200 };
		const float k_spring_force{ 1 };

		sf::CircleShape m_shape;
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
		Sound m_bounce_sound;
	};
}