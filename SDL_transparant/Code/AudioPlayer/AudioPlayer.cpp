#include "AudioPlayer.hpp"
#include "../common.hpp"
//#include "../Utilities/FileManipulation.hpp"
#include <fstream>

AudioPlayer::AudioPlayer()
{
    //Get config file
    std::fstream file("../config.json", std::ios::in);
	if (!file.is_open())
	{
        std::cout << "CRITICAL ERROR : cannot open json file config file" << std::endl;
		return;
	}
 

	try
	{
        file >> config;
	}
	catch (const std::exception& e)
	{
        std::cout << "CRITICAL ERROR : JSON parse failed for config " << e.what() << std::endl;
		file.close();
		return;
	}
	file.close();
    
    //Check if music folder is configured
    const std::string& folderPath = config["music-folder-path"].asString();

    std::cout << "folder path : " << folderPath << std::endl;

    if (folderPath != "")
    {

    }



}

AudioPlayer::~AudioPlayer()
{
}
