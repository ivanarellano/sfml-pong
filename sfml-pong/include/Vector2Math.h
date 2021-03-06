#pragma once
#include <SFML\System\Vector2.hpp>
#include <cmath>

namespace Vec2Math
{
	inline float mag(const sf::Vector2f& a)
	{
		return std::sqrtf(a.x * a.x + a.y * a.y);
	}

	inline sf::Vector2f norm(const sf::Vector2f& a)
	{
		float m{ mag(a) };
		if (m == 0) return a;

		return sf::Vector2f{ a } / mag(a);
	}

	inline sf::Vector2f limit(const sf::Vector2f& a, float n)
	{
		if (mag(a) > n)
			return norm(a) * n;
		else
			return a;
	}
}