#pragma once
#include "Sound.h"
#include "Actor.h"

namespace Pong
{
	class Ball : public Actor
	{
	public:
		enum class Direction
		{
			None, NW, NE, SW, SE
		};

		explicit Ball(sf::Vector2f size = sf::Vector2f{ 10.f, 10.f });

		void update(float dt) override;

		void increase_velocity(float vel);
		void reflect_on_court();
		void reflect_on_paddle();

		void reset_velocity() { m_velocity = k_min_velocity; }
		void set_direction(Direction dir) { m_direction = dir; }
	private:
		const float k_min_velocity{ 300 };
		const float k_max_velocity{ 500 };
		const float k_spring_force{ 50 };

		float m_velocity{ k_min_velocity };
		Direction m_direction{ Direction::None };

		Sound m_bounce_sound;
	};
}