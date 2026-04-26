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
		~MiniAudio();

		int PlayMusic(const char* _filePath);
		bool MusicIsPlaying(void);

		void SetVolume(float _volume);
		const float GetVolume(void);


	private:

		//Initialisation de MiniAudio
		ma_engine* engine = nullptr; 
		ma_sound* sound = nullptr;
		MusicState state = NOTHING;

};