#include "HalfCourtLine.h"
#include "Window.h"

namespace Pong
{
	HalfCourtLine::HalfCourtLine(int height, int width, sf::Vector2f size, float gap)
		: m_dash_width { size.x }
		, m_dash_height { size.y }
	{
		if (gap < 1 || m_dash_width < 1 || m_dash_height < 1)
			return;

		for (float y_offset = 0; y_offset < height; y_offset += m_dash_height + gap)
		{
			sf::RectangleShape rect { sf::Vector2f{ m_dash_width, m_dash_height } };

			rect.setPosition(static_cast<float>(width / 2 - m_dash_width / 2), m_dash_height + y_offset);
			m_notches.push_back(rect);
		}
	}

	void HalfCourtLine::draw(sf::RenderTarget* target)
	{
		for (auto& notch : m_notches)
			target->draw(notch);
	}
}
