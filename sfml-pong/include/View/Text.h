#pragma once
#include "Font.h"
#include "Widget.h"
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <functional>

namespace Pong
{
	struct TextStyle
	{
		TextStyle();

		Font::Asset m_font;
		unsigned int m_size;
		sf::Color m_color;
	};

	using TextStates = std::unordered_map<ViewState, TextStyle>;

	struct Text : Widget
	{
		explicit Text(const std::string& text = "");
		Text(const std::string& text, OnClickCallback callback);

		void on_click(Address pw) override;

		void draw(sf::RenderTarget* window) override { if (is_visible()) window->draw(m_text); }

		void set_text(const std::string& text) { m_text.setString(text); }
		void set_size(unsigned int size) { m_text.setCharacterSize(size); }
		void set_color(sf::Color color) { m_text.setFillColor(color); }
		void set_font(Font::Asset asset)
		{
			m_font.loadFromFile(Font::get_path(asset)); 
			m_text.setFont(m_font);
		}

		void set_style(const ViewState& state, const TextStyle& style);
		void apply_style();
	private:
		sf::Text m_text;
		sf::Font m_font;
		TextStates m_style_states;
		OnClickCallback m_on_click_cb;
	};
}
