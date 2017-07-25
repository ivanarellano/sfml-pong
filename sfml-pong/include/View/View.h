#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Pong
{
	class Drawable
	{
	public:
		virtual ~Drawable() {}

		virtual void draw(sf::RenderTarget* target) = 0;
	};

	class Measurement
	{
	public:
		virtual ~Measurement() {}

		virtual sf::FloatRect get_bounds() const = 0;
	};

	class Movable
	{
	public:
		virtual ~Movable() {}

		virtual sf::Vector2f get_position() const = 0;
		virtual void set_position(float x, float y) = 0;
		virtual void move(float x, float y) = 0;
	};

	class View : Drawable, Measurement, Movable
	{
	public:
		virtual ~View() {}

		bool is_visible() const { return m_visibility ? true : false; }

		void set_visibility(bool visibility) { m_visibility = visibility; }
	private:
		bool m_visibility { true };
	};
}
