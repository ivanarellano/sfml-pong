#pragma once
#include "Screen.h"

namespace Pong
{
	class TitleScreen : public Screen
	{
	public:
		void draw(sf::RenderTarget* target) override;
		void on_start() override;
		void update(float dt) override;
		void handle_input(sf::Event event) override;
		void on_stop() override;
	};
}
