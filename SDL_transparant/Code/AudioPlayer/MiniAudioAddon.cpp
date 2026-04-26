#include "MiniAudioAddon.hpp"
#include <cstdlib>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


MiniAudio::MiniAudio()
{
    engine = new ma_engine();
    sound = new ma_sound();

    if (ma_engine_init(NULL, engine) != MA_SUCCESS)
    {
        std::cout << "error on loading mini audio engine\n";
        exit(EXIT_FAILURE);
    }
}
MiniAudio::~MiniAudio()
{
    ma_sound_uninit(sound);
    ma_engine_uninit(engine);
    
    delete sound;
    delete engine;
}


//Lecture du fichier audio
int MiniAudio::PlayMusic(const char* _filePath)
{
    ma_sound_uninit(sound);
    
    ma_result result = ma_sound_init_from_file(engine, _filePath, 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
    {
        std::cerr << "[MA] Erreur lors du chargement du son, code miniaudio : " << result << std::endl;
        return -1;
    }

    if (ma_sound_start(sound) != MA_SUCCESS)
    {
        std::cerr << "[MA] Erreur lors du lancement du son, code miniaudio : " << result << std::endl;
    }
    else
    {
        std::cerr << "[MA] play : " << _filePath << std::endl;
    }

    return 0;
}

bool MiniAudio::MusicIsPlaying(void)
{
    return ma_sound_is_playing(sound);
}

void MiniAudio::SetVolume(float _volume)
{
    ma_sound_set_volume(sound, _volume);
}
const float MiniAudio::GetVolume(void)
{
    return ma_sound_get_volume(sound);
}