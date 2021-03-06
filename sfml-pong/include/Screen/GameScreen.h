#pragma once
#include "Screen.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"
#include "HalfCourtLine.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

namespace Pong
{
	class GameScreen : public Screen
	{
	public:
		enum class PlayState
		{
			Playing, Serving, Won
		};

		explicit GameScreen(sf::Vector2u screen_size);
		
		virtual void serve();

		void on_start() override;
		void tick(float delta_time) override;
		void handle_input(sf::Event event, Game* game) override;
		void draw(sf::RenderTarget* target) const override;
	private:
		const int k_serve_delay_sec{ 3 };

		float k_paddle_hori_padding{ 35.f };
		float k_score_vert_padding{ 60.f };

		int m_p1_score{ 0 };
		int m_p2_score{ 0 };
		PlayState m_state{ PlayState::Serving };

		Paddle* m_server{ nullptr };
		float m_serve_delay_dt{ 0.f };

		Ball m_ball{ 0, m_screen_size.y };
		Text m_p1_score_text;
		Text m_p2_score_text;
		Text m_winner_text;
		Paddle m_p1{ Paddle::Player::P1, 0, m_screen_size.y };
		Paddle m_p2{ Paddle::Player::P2, 0, m_screen_size.y };
		Text m_press_key_text{ "Press any key\nto play again." };
		HalfCourtLine m_half_court_line{ m_screen_size };

		Paddle* did_player_win();
		void check_scoring();
		void show_winner(const std::string& name);
	};
}