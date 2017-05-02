#pragma once
#include "Resources.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

namespace Pong
{
	class Sound
	{
	public:
		enum Asset
		{
			blip
		};

		Sound() {}

		void load(const Asset& asset)
		{
			if (m_buffer.loadFromFile(get_path(asset)))
				m_sound.setBuffer(m_buffer);
		}

		void play() { if (m_sound.getBuffer() != nullptr) m_sound.play(); }

		static std::string get_path(Asset asset)
		{
			std::string base = get_assets_path();

			switch (asset)
			{
			case blip: return base + "blip.wav";
			default: return "";
			}
		}

	private:
		sf::SoundBuffer m_buffer;
		sf::Sound m_sound;
	};
}