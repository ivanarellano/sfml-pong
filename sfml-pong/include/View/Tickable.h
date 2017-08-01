#pragma once

namespace Pong
{
	class Tickable
	{
	public:
		virtual ~Tickable() {}

		virtual void tick(float delta_time) = 0;
	};
}