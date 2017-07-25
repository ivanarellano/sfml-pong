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

		Ball();

		explicit Ball(sf::Vector2f size, float start_velocity, float max_velocity, float spring_force)
			: Actor { size }
			, k_start_velocity { start_velocity }
			, k_max_velocity { max_velocity }
			, k_spring_force { spring_force }
			, m_velocity { start_velocity }
			, m_direction { Direction::None }
		{
		}

		void update(float dt) override;

		void increase_velocity(float vel);
		void reflect_on_court();
		void reflect_on_paddle();

		void reset_velocity() { m_velocity = k_start_velocity; }
		void set_direction(Direction dir) { m_direction = dir; }
	private:
		const float k_start_velocity;
		const float k_max_velocity;
		const float k_spring_force;

		float m_velocity;
		Direction m_direction;
		Sound m_bounce_sound;
	};
}