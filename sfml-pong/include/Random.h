#pragma once
#include <random>

namespace Pong
{
	inline int random(int min, int max)
	{
		static std::default_random_engine random_engine;
		random_engine.seed(std::random_device{}());
		return std::uniform_int_distribution<>{min, max}(random_engine);
	}

	inline bool coin_toss() { return random(0, 1); }
}