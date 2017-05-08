#pragma once
#include "View.h"

namespace Pong
{
	enum class ViewState
	{
		Neutral, Focused, Clicked
	};

	class Widget : public View
	{
	public:
		virtual ~Widget() {}

		virtual void on_click() = 0;
	protected:
		ViewState m_state { ViewState::Neutral };
	};
}
