#pragma once
#include "View.h"

namespace Pong
{
	class Widget : public View
	{
	public:
		virtual ~Widget() {}

		virtual void read_in(std::stringstream& stream) = 0;
		virtual void on_click(const sf::Vector2f& mouse_pos) = 0;
		virtual void on_release() = 0;
	};
}
