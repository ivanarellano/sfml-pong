#pragma once

namespace Pong
{
	class Measurement
	{
	public:
		virtual ~Measurement() {}

		virtual float get_width() const = 0;
		virtual float get_height() const = 0;
	};
}