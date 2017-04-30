#pragma once
#include "Measurement.h"
#include "Movable.h"
#include "Font.h"
#include <SFML/Graphics/Text.hpp>

namespace Pong
{
	struct Text : Drawable, Measurement, Movable
	{
		explicit Text(Font::Asset asset = Font::forward, int size = 50) : m_visibility(Visibility::Visible)
		{
			m_font.loadFromFile(Font::get_path(asset));

			m_text.setFont(m_font);
			m_text.setFillColor(sf::Color::White);

			set_size(size);
		}

		float get_width() const override { return m_text.getGlobalBounds().width; }
		float get_height() const override { return m_text.getGlobalBounds().height; }

		void draw(sf::RenderWindow* window) override { if (is_visible()) window->draw(m_text); }
		void set_position(float x, float y) override { m_text.setPosition(x, y); }
		void move(float x, float y) override { m_text.move(x, y); }

		sf::Vector2f get_position() const { return m_text.getPosition(); }
		bool is_visible() const { return m_visibility == Visibility::Visible ? true : false; }

		void set_text(const std::string& text) { m_text.setString(text); }
		void set_size(int size) { m_text.setCharacterSize(size); }
		void set_visibility(Visibility vis) { m_visibility = vis; }
	private:
		sf::Text m_text;
		sf::Font m_font;
		Visibility m_visibility;
	};
}