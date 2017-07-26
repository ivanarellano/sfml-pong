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

		void initialize();
		void on_collision();

		void increase_velocity(float vel);
	private:
		const float k_min_velocity{ 300 };
		const float k_max_velocity{ 500 };
		const float k_spring_force{ 50 };

		sf::Vector2f m_velocity;

		Sound m_bounce_sound;
	};
}