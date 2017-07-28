#pragma once

namespace Pong
{
	using Address = void*;
	using OnClickCallback = void(*)(Address);

	template<class W> W& reference_to(Address pw)
		// treat an address as a reference to a W
	{
		return *static_cast<W*>(pw);
	}

	enum class ViewState
	{
		Neutral, Focused, Clicked
	};

	class Widget
	{
	public:
		virtual ~Widget() {}

		virtual void on_click(Address) = 0;
	protected:
		ViewState m_state { ViewState::Neutral };
	};
}
