#pragma once
#include "Screen.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"
#include "HalfCourtLine.h"
#include <random>

namespace Pong
{
	inline int random(int min, int max)
	{
		static std::default_random_engine random_engine;
		random_engine.seed(std::random_device{}());
		return std::uniform_int_distribution<>{min, max}(random_engine);
	}

	inline bool coin_toss() { return random(0, 1); }

	class GameScreen : public Screen
	{
	public:
		enum class PlayState
		{
			Playing, Serving, Won
		};

		GameScreen();

		GameScreen(float paddle_offset, float score_offset, int serve_delay)
			: k_serve_delay { serve_delay }
			, k_paddle_offset { paddle_offset }
			, k_score_offset { score_offset }
			, m_p1_score { 0 }
			, m_p2_score { 0 }
			, m_state { PlayState::Serving }
			, m_server { nullptr }
			, m_time { 0 } {}

		virtual void serve();

		void on_start() override;
		void update(float dt) override;
		void draw(sf::RenderTarget* target) override;
		void handle_input(sf::Event event) override;

		void on_stop() override {}

	private:
		const int k_serve_delay;
		const float k_paddle_offset;
		const float k_score_offset;

		int m_p1_score;
		int m_p2_score;
		PlayState m_state;

		Ball m_ball;
		Paddle m_player_1;
		Paddle m_player_2;
		Text m_p1_score_view;
		Text m_p2_score_view;
		HalfCourtLine m_half_court_line;
		Text m_winner_text;
		Text m_press_key_text;

		Paddle* m_server;
		sf::Clock m_clock;
		float m_time;

		Paddle* did_player_win();
		void show_winner(std::string name);

		bool can_go_up(const sf::RectangleShape& shape);
		bool can_go_down(const sf::RectangleShape& shape);
	};
}