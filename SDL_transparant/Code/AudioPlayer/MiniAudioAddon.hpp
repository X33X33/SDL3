#pragma once
//#include "../common.hpp"
#include <iostream>
#include <string>
#include "miniaudio.h"

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
		ma_engine engine;
		ma_sound sound;
		MusicState state;

};