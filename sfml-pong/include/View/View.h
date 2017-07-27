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

	class Tickable
	{
	public:
		virtual ~Tickable() {}

		virtual void tick(float delta_time) = 0;
	};

	class View : Drawable
	{
	public:
		virtual ~View() {}

		bool is_visible() const { return m_visibility ? true : false; }

		void set_visibility(bool visibility) { m_visibility = visibility; }
	private:
		bool m_visibility { true };
	};
}
