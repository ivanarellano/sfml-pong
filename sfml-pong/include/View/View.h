#pragma once
#include "Movable.h"
#include "Measurement.h"
#include "Drawable.h"

namespace Pong
{
	class View : Drawable, Measurement, Movable
	{
	public:
		enum class Visibility
		{
			Visible, Gone
		};

		virtual ~View() {}

		virtual void update(float dt) = 0;

		bool is_visible() const { return m_visibility == Visibility::Visible ? true : false; }

		void set_visibility(Visibility vis) { m_visibility = vis; }
	private:
		Visibility m_visibility { Visibility::Visible };
	};
}
