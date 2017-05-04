#include "Text.h"

namespace Pong
{
	TextStyle::TextStyle()
		: m_font { Font::forward }
		, m_size { 50 }
		, m_color { sf::Color::White }
	{
	}

	Text::Text()
	{
		TextStyle style;
		set_style(ViewState::Neutral, style);
		apply_style();
	}

	void Text::read_in(std::stringstream& stream)
	{
	}

	void Text::on_click(const sf::Vector2f& mouse_pos)
	{
	}

	void Text::on_release()
	{
	}

	void Text::update(float dt) { /* No-op */}

	void Text::set_style(const ViewState& state, const TextStyle& style)
	{
		m_style_states[state] = style;
	}

	void Text::apply_style()
	{
		auto itr { m_style_states.find(m_state) };
		if (itr == m_style_states.end())
			return;

		TextStyle style { itr->second };

		set_font(style.m_font);
		set_color(style.m_color);
		set_size(style.m_size);
	}
}
