#pragma once
#include "Screen.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"
#include "HalfCourtLine.h"
#include <SFML\System\Clock.hpp>

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
		const int k_serve_delay_sec{ 3 };
		const float k_paddle_hori_padding{ 35.f };
		const float k_score_vert_padding{ 40.f };

		void init_gui();

		int m_p1_score{ 0 };
		int m_p2_score{ 0 };
		PlayState m_state{ PlayState::Serving };

		Ball m_ball;
		Paddle m_p1;
		Paddle m_p2;
		Text m_p1_score_text;
		Text m_p2_score_text;
		Text m_winner_text;
		Text m_press_key_text{ "Press any key\nto play again." };
		HalfCourtLine m_half_court_line{ m_screen_size };
		Paddle* m_server{ nullptr };
		float m_time{ 0.f };

		Paddle* did_player_win();
		void show_winner(std::string name);

		bool can_go_up(const sf::RectangleShape& shape);
		bool can_go_down(const sf::RectangleShape& shape);
	};
}