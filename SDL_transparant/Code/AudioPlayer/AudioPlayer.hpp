#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP

#include "MiniAudioAddon.hpp"
#include "../Utilities/jsoncpp.cpp"
#include "../Utilities/json/json.h"


class AudioPlayer
{
public:

    AudioPlayer();
    ~AudioPlayer();




private:

    Json::Value config;




};

#endif //!AUDIO_PLAYER_HPP