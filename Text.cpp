#include "Text.h"

namespace Pong
{
	Text::Text()
	{
		TextStyle style;
		set_style(style);
	}

	void Text::set_style(const TextStyle& style)
	{
		set_font(style.m_font);
		set_color(style.m_color);
		set_size(style.m_size);
	}

	TextStyle::TextStyle() 
		: m_font { Font::forward }
		, m_size { 50 }
		, m_color { sf::Color::White }
	{
	}
}
