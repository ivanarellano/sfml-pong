#pragma once
#include "Font.h"
#include "View.h"
#include <SFML/Graphics/Text.hpp>

namespace Pong
{
	enum class ViewState
	{
		Neutral, Focused, Clicked
	};

	struct TextStyle
	{
		TextStyle();

		Font::Asset m_font;
		unsigned int m_size;
		sf::Color m_color;
	};

	struct Text : View
	{
		Text();

		void update(float dt) override {}

		float get_width() const override { return m_text.getGlobalBounds().width; }
		float get_height() const override { return m_text.getGlobalBounds().height; }

		void draw(sf::RenderTarget* window) override { if (is_visible()) window->draw(m_text); }
		void set_position(float x, float y) override { m_text.setPosition(x, y); }
		void move(float x, float y) override { m_text.move(x, y); }

		sf::Vector2f get_position() const { return m_text.getPosition(); }

		void set_text(const std::string& text) { m_text.setString(text); }
		void set_size(unsigned int size) { m_text.setCharacterSize(size); }
		void set_color(sf::Color color) { m_text.setFillColor(color); }
		void set_font(Font::Asset asset)
		{
			m_font.loadFromFile(Font::get_path(asset)); 
			m_text.setFont(m_font);
		}

		void set_style(const TextStyle& style);
	private:
		sf::Text m_text;
		sf::Font m_font;
	};
}
