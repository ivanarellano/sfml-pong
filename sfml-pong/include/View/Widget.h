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

		virtual void on_click() = 0;
		virtual void on_release() = 0;
	protected:
		ViewState m_state { ViewState::Neutral };
	};
}
