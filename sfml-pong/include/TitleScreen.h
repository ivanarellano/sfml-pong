#pragma once
#include "Client.h"
#include "Screen.h"
#include "Server.h"
#include "Text.h"
#include "Window.h"

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

		Client m_client;
		Server m_server;

		static void cb_new_game(Address pw) { reference_to<TitleScreen>(pw).start_game_server(); }
		static void cb_join_game(Address pw) { reference_to<TitleScreen>(pw).find_game_server(); }
		static void cb_credits(Address pw) { reference_to<Window>(pw).show_credits_screen(); }
	};
}
