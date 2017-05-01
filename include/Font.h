#pragma once
#include "Resources.h"
#include <string>

namespace Pong
{
	struct Font
	{
		enum Asset
		{
			forward
		};

		static std::string get_path(Asset type)
		{
			std::string base = get_assets_path();

			switch (type)
			{
			case forward: return base + "FFFFORWA.TTF";
			default: return "";
			}
		}
	};
}