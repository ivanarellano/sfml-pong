#pragma once
#include "View.h"

namespace Pong
{
	enum class ElementType {
		Label, Button
	};

	enum class ViewState
	{
		Neutral, Focused, Clicked
	};

	class Widget : public View
	{
	public:
		virtual ~Widget() {}

		virtual void read_in(std::stringstream& stream) = 0;
		virtual void on_click(const sf::Vector2f& mouse_pos) = 0;
		virtual void on_release() = 0;

		friend std::stringstream& operator>>(std::stringstream& stream, Widget& widget)
		{
			widget.read_in(stream);
			return stream;
		}
	protected:
		ViewState m_state { ViewState::Neutral };
	};
}
