#include "Text.h"

namespace Pong
{
	Text::Text(const std::string& text, OnClickCallback callback)
		: sf::Text{}
		, m_on_click_cb { callback }
	{
		TextStyle style;
		set_style(ViewState::Neutral, style);
		setString(text);
	}

	void Text::on_click(Address pw)
	{
		if (m_on_click_cb != nullptr) m_on_click_cb(pw);
	}

	void Text::set_style(const ViewState& state, const TextStyle& style)
	{
		m_style_states[state] = style;

		if (state == m_state) apply_style();
	}

	void Text::apply_style()
	{
		auto itr { m_style_states.find(m_state) };

		if (itr == m_style_states.end()) return;

		TextStyle style { itr->second };
		set_font(style.m_font);
		setFillColor(style.m_color);
		setCharacterSize(style.m_size);
	}
}
