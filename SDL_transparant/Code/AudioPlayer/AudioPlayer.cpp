#include "AudioPlayer.hpp"
#include "../common.hpp"
#include "../Utilities/FileManipulation.hpp"
#include "MiniAudioAddon.hpp"
#include <fstream>
#include <vector>

AudioPlayer::AudioPlayer()
{
    //Get config file
    std::fstream file("../Assets/config.json", std::ios::in);
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
		std::vector<std::string> filesInFolder = GetFilesInFolder(folderPath);


		for (std::string& file : filesInFolder)
		{
			//std::cout << file << std::endl;

			if (GetFileTypeEnum(file) == FileType::MUSIC)
			{
				musicsPath.push_back(file);
			}
		}
		for (std::string& musics : musicsPath)
		{
			std::cout << musics << std::endl;
		}
    }

	//miniAudio.PlayMusic("/home/benoit/Documents/Programation/Projets/Git/SDL3/SDL_transparant/Assets/03. CHIHIRO.flac");
	miniAudio.PlayMusic(musicsPath[1].c_str());

}

AudioPlayer::~AudioPlayer()
{
}
