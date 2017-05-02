#pragma once
#include "Drawable.h"

namespace Pong
{
	struct Screen : Drawable
	{
		virtual ~Screen() {}

		virtual void on_start() = 0;
		virtual void update(float dt) = 0;
		virtual void handle_input(sf::Event event) = 0;
		virtual void on_stop() = 0;

		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
	protected:
		Screen() {}
	};
}