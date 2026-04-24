#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP

#include "MiniAudioAddon.hpp"
#include "../Utilities/json/json.h"


class AudioPlayer
{
public:

    AudioPlayer();
    ~AudioPlayer();




private:

    Json::Value config;
    std::vector<std::string> musicsPath;
    MiniAudio miniAudio;


};

#endif //!AUDIO_PLAYER_HPP