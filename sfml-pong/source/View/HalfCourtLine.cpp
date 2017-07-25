#include "HalfCourtLine.h"
#include "Window.h"

namespace Pong
{
	HalfCourtLine::HalfCourtLine(sf::Vector2u screen_sz, sf::Vector2i dash_sz, int gap)
	{
		if (gap < 1 || dash_sz.x < 1 || dash_sz.y < 1) return;

		for (float y_offset = 0; y_offset < screen_sz.y; y_offset += dash_sz.y + gap)
		{
			sf::RectangleShape rect{ sf::Vector2f{ dash_sz } };

			rect.setPosition(static_cast<float>(screen_sz.x / 2 - dash_sz.x / 2), dash_sz.y + y_offset);
			m_notches.push_back(rect);
		}
	}

	void HalfCourtLine::draw(sf::RenderTarget* target)
	{
		for (const auto& notch : m_notches) target->draw(notch);
	}
}
