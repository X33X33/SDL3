#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP

#include "MiniAudioAddon.hpp"
#include "../Utilities/json/json.h"
#include "../Utilities/SqliteAddon.hpp"


class AudioPlayer
{
public:

    AudioPlayer();
    ~AudioPlayer();


    void Update(float _dt);

    MiniAudio miniAudio;


private:

    void Setup(void);

    Json::Value config;
    SqliteTool musicsDB;
    std::vector<std::string> musicsPath;

    unsigned long m_nbOfMusics = 0;
};

#endif //!AUDIO_PLAYER_HPP