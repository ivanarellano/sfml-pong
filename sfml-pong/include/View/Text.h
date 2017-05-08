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
	using OnClickCallback = std::function<void()>;

	struct Text : Widget
	{
		Text();
		explicit Text(OnClickCallback callback);

		void on_click() override;
		void update(float dt) override;

		sf::FloatRect get_bounds() const override { return m_text.getGlobalBounds(); }
		void draw(sf::RenderTarget* window) override { if (is_visible()) window->draw(m_text); }

		sf::Vector2f get_position() const override { return m_text.getPosition(); }
		void set_position(float x, float y) override { m_text.setPosition(x, y); }
		void move(float x, float y) override { m_text.move(x, y); }

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
