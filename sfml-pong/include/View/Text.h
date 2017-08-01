#pragma once
#include "Font.h"
#include "Widget.h"
#include "Visibility.h"
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <functional>

namespace Pong
{
	struct TextStyle
	{
		Font::Asset m_font{ Font::forward };
		unsigned int m_size{ 50 };
		sf::Color m_color{ sf::Color::White };
	};

	using TextStates = std::unordered_map<ViewState, TextStyle>;

	struct Text : Widget, Visibility, sf::Text
	{
		explicit Text(const std::string& text = "") : Text{ text, nullptr } 
		{
		}

		Text(const std::string& text, OnClickCallback callback);

		void set_font(Font::Asset asset)
		{
			m_font.loadFromFile(Font::get_path(asset)); 
			setFont(m_font);
		}

		void on_click(Address pw);
		void set_style(const ViewState& state, const TextStyle& style);
		void apply_style();

		float get_half_width() { return getGlobalBounds().width / 2.f; }
		float get_half_height() { return getGlobalBounds().height / 2.f; }
	private:
		sf::Font m_font;
		TextStates m_style_states;
		OnClickCallback m_on_click_cb;
	};
}
