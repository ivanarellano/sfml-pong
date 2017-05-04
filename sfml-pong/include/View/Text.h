#pragma once
#include "Font.h"
#include "Widget.h"
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>

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
		Text();

		void read_in(std::stringstream& stream) override;
		void on_click(const sf::Vector2f& mouse_pos) override;
		void on_release() override;
		void update(float dt) override;

		sf::FloatRect get_bounds() const override { return m_text.getGlobalBounds(); }

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

		void set_style(const ViewState& state, const TextStyle& style);
		void apply_style();
	private:
		sf::Text m_text;
		sf::Font m_font;
		TextStates m_style_states;
	};
}
