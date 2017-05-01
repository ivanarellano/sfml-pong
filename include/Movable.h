#pragma once

namespace Pong
{
	class Movable
	{
	public:
		virtual ~Movable() {}

		virtual void set_position(float x, float y) = 0;
		virtual void move(float x, float y) = 0;
	};
}