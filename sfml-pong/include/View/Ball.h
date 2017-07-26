#pragma once
#include "Sound.h"
#include "Actor.h"

namespace Pong
{
	class Ball : public Actor
	{
	public:
		explicit Ball(sf::Vector2f size = sf::Vector2f{ 10.f, 10.f });

		void update(float dt) override;

		void serve(bool isFacingLeftPlayer);
		void increase_velocity(float vel);
		void on_collision();
	private:
		const float k_min_velocity{ 100.f };
		const float k_max_velocity{ 200 };
		const float k_spring_force{ 1 };

		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;

		Sound m_bounce_sound;
	};
}