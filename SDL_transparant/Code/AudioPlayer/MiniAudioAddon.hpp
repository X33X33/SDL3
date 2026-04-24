#pragma once
//#include "../common.hpp"
#include <iostream>
#include <string>

struct ma_engine; 
struct ma_sound;


enum MusicState
{
	NOTHING,
	PLAYING,
	PAUSE,
	STOP
};


class MiniAudio
{
	public:

		MiniAudio();

		int PlayMusic(const char* _filePath);
		void Cleanup();

	private:

		//Initialisation de MiniAudio
		ma_engine* engine = nullptr; 
		ma_sound* sound = nullptr;
		MusicState state = NOTHING;

};