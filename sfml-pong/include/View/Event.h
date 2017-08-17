#pragma once

namespace Pong
{
	enum class EventType
	{
		None, Click, Release
	};

	struct ClickCoordinates
	{
		float x;
		float y;
	};

	struct Event
	{
		EventType m_type;
		const char* m_element;
		const char* m_interface;

		union
		{
			ClickCoordinates m_clickCoords;
		};
	};
}