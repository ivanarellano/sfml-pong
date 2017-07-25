#pragma once
#include "Drawable.h"

namespace Pong
{
	class Window;

	struct Screen : Drawable
	{
		virtual ~Screen() {}

		virtual void on_start() = 0;
		virtual void update(float dt) = 0;
		virtual void handle_input(sf::Event event, Window* window) = 0;

		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
	protected:
		explicit Screen(sf::Vector2u screen_size) : m_screen_size(screen_size) {}

		sf::Vector2u m_screen_size;
	};
}