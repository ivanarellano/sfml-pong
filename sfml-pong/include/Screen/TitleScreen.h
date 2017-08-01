#pragma once
#include "Game.h"
#include "Screen.h"
#include "Text.h"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace Pong
{
	class TitleScreen : public Screen
	{
	public:
		explicit TitleScreen(sf::Vector2u screen_size);

		void on_start() override;
		void tick(float delta_time) override { /* Do nothing*/ }
		void handle_input(sf::Event event, Game* game) override;
		void draw(sf::RenderTarget* target) const override;
	private:
		Text m_title{ "PONG" };
		Text m_host_game{ "New Game (LAN)", cb_new_game };
		Text m_join_game{ "Join Game (LAN)", cb_join_game };
		Text m_credits{ "Credits", cb_credits };

		static void cb_new_game(Address pw) { reference_to<Game>(pw).show_game_screen(); }
		static void cb_join_game(Address pw) { reference_to<Game>(pw).show_game_screen(); }
		static void cb_credits(Address pw) { reference_to<Game>(pw).show_credits_screen(); }
	};
}
