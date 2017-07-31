#include "Paddle.h"
#include <SFML/Window/Keyboard.hpp>

namespace Pong
{
	void Paddle::tick(float delta_time)
	{
		float speed{ m_move_speed * delta_time };

		switch (m_player)
		{
		case Player::P1:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move_up();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move_down();
			break;
		default:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move_up();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move_down();
		}
	}
}