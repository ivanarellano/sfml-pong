#pragma once
#include "Screen.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"
#include "HalfCourtLine.h"

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

		void draw(sf::RenderTarget* target) override;
		void on_start() override;
		void update(float dt) override;
		void handle_input(sf::Event event, Game* game) override;
	private:
		const int k_serve_delay{ 3 };
		const float k_paddle_offset{ 35.f };
		const float k_score_offset{ 40.f };

		int m_p1_score;
		int m_p2_score;
		PlayState m_state;

		Ball m_ball;
		Paddle m_player_1;
		Paddle m_player_2;
		Text m_p1_score_text;
		Text m_p2_score_text;
		Text m_winner_text;
		Text m_press_key_text;
		HalfCourtLine m_half_court_line {100, 1};

		Paddle* m_server;
		sf::Clock m_clock;
		float m_time;

		Paddle* did_player_win();
		void show_winner(std::string name);

		bool can_go_up(const sf::RectangleShape& shape);
		bool can_go_down(const sf::RectangleShape& shape);
	};
}