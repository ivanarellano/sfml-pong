#pragma once
#include "Window.h"
#include "Screen.h"
#include "Text.h"

namespace Pong
{
	class TitleScreen : public Screen
	{
	public:
		TitleScreen();

		void start_game_server();
		void find_game_server();

		void draw(sf::RenderTarget* target) override;
		void on_start() override;
		void update(float dt) override;
		void handle_input(sf::Event event, Window* window) override;
		void on_stop() override;
	private:
		Text m_title;
		Text m_host_game;
		Text m_join_game;
		Text m_credits;

		static void cb_new_game(Address pw) { reference_to<TitleScreen>(pw).start_game_server(); }
		static void cb_join_game(Address pw) { reference_to<TitleScreen>(pw).find_game_server(); }
		static void cb_credits(Address pw) { reference_to<Window>(pw).show_credits_screen(); }
	};
}
