#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Pong
{
	class Game;

	struct Screen
	{
		virtual ~Screen() {}

		virtual void on_start() = 0;
		virtual void update(float dt) = 0;
		virtual void handle_input(sf::Event event, Game* game) = 0;
		virtual void draw(sf::RenderTarget* target) const = 0;

		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
	protected:
		explicit Screen(sf::Vector2u screen_size) : m_screen_size{ screen_size } {}

		sf::Vector2u m_screen_size;
	};
}