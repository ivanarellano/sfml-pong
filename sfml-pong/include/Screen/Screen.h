#pragma once
#include "Tickable.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Pong
{
	class Game;

	struct Screen : Tickable
	{
		virtual ~Screen() {}

		virtual void on_start() = 0;
		virtual void handle_input(sf::Event event, Game* game) = 0;
		virtual void draw(sf::RenderTarget* target) const = 0;

		float get_half_screen_width() { return m_screen_size.x / 2.f; }
		float get_half_screen_height() { return m_screen_size.y / 2.f; }

		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
	protected:
		explicit Screen(sf::Vector2u screen_size) : m_screen_size{ screen_size } {}

		sf::Vector2u m_screen_size;
	};
}