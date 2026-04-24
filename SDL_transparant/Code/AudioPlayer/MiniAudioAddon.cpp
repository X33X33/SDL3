#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "MiniAudioAddon.hpp"

MiniAudio::MiniAudio()
{
    state = NOTHING;

    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        std::cout << "error on loading mini audio engine\n";
        //return -1;
    }
}

//Lecture du fichier audio
int MiniAudio::PlayMusic(const char* _filePath)
{
    if (!ma_sound_init_from_file(&engine, _filePath, 0, NULL, NULL, &sound))
    {
        std::cerr << "Erreur lors du chargement du son\n";
        return -1;
    }

    ma_sound_start(&sound);  // lecture


    return 0;
}

void MiniAudio::Cleanup()
{
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
}
