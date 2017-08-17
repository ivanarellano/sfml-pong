#pragma once
#include <string>

#ifdef TARGET_OS_MAC
	#include "ResourcePath.hpp"
#endif

namespace Pong
{
	inline std::string get_assets_path()
	{
		std::string project_assets_path { "assets/" };
		#ifdef TARGET_OS_MAC
			return resourcePath() + project_assets_path;
		#else
			return project_assets_path;
		#endif
	}
}