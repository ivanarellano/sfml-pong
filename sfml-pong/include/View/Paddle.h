#pragma once
#include "Tickable.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <string>
#include <iostream>

namespace Pong
{
	class Paddle : public sf::RectangleShape, public Tickable
	{
	public:
		enum class Player
		{
			P1, P2
		};

		Paddle(Player player, int top_bound = { 0 }, 
			int btm_bound = { 0 }, sf::Vector2f size = sf::Vector2f{ 16.f, 50.f })
			: RectangleShape{ size }
			, m_player{ player }
			, m_top_y_bound{top_bound}
			, m_btm_y_bound{btm_bound}
		{
		}

		void tick(float delta_time) override;

		const std::string get_name() { return m_player == Player::P1 ? "P1" : "P2"; }

		void move_up()
		{
			if (getPosition().y - get_half_height() >= m_top_y_bound)
			{
				move(0, -m_move_speed);
			}
		}

		void move_down()
		{
			if (getPosition().y + get_half_height() <= m_btm_y_bound)
			{
				move(0, m_move_speed);
			}
		}

		float get_half_width() { return getSize().x / 2.f; }
		float get_half_height() { return getSize().y / 2.f; }
	private:
		Player m_player;
		float m_move_speed{ 10.f };
		int m_top_y_bound;
		int m_btm_y_bound;
	};
}