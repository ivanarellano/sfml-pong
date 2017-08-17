#pragma once

namespace Pong
{
	class Visibility
	{
	public:
		virtual ~Visibility() {}

		bool is_visible() const { return m_visibility ? true : false; }
		void set_visibility(bool visibility) { m_visibility = visibility; }
	private:
		bool m_visibility { true };
	};
}
