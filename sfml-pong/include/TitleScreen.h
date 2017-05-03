#pragma once
#include "Screen.h"
#include "Text.h"

namespace Pong
{
	class TitleScreen : public Screen
	{
	public:
		TitleScreen();

		virtual void new_game();
		virtual void join_game();

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
	};
}
