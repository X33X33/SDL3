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

//Lecture du fichier audio
int MiniAudio::PlayMusic(const char* _filePath)
{
    ma_result result = ma_sound_init_from_file(engine, _filePath, 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
    {
        std::cerr << "Erreur lors du chargement du son, code miniaudio : " << result << std::endl;
        return -1;
    }

    ma_sound_start(sound);


    return 0;
}

void MiniAudio::Cleanup()
{
    ma_sound_uninit(sound);
    ma_engine_uninit(engine);

    delete sound;
    delete engine;

}
