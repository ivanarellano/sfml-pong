#pragma once
#include "Screen.h"
#include "Text.h"
#include "Window.h"

namespace Pong
{
	class TitleScreen : public Screen
	{
	public:
		TitleScreen();

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

		static void cb_new_game(Address pw) { std::cout << "New game clicked" << std::endl; }
		static void cb_join_game(Address pw) { std::cout << "Join game clicked" << std::endl; }
		static void cb_credits(Address pw) { reference_to<Window>(pw).show_credits_screen(); }
	};
}
