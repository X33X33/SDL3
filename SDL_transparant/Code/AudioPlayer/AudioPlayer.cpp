#include "AudioPlayer.hpp"

#include "../common.hpp"
#include "../Utilities/FileManipulation.hpp"
#include <fstream>
#include <string>
#include <vector>

AudioPlayer::AudioPlayer()
{
    Setup();
}
AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::Setup(void)
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
        std::cerr << "CRITICAL ERROR : JSON parse failed for config " << e.what() << std::endl;
		file.close();
		return;
	}
	file.close();
    
    //Check if music folder is configured
    std::string folderPath = config["music-folder-path"].asString();

	
	while (!FolderExist( folderPath))
	{
		//Reset var if user enter retry this fonction (invalid path)
		folderPath = "";

		std::cerr << "Your folder PATH of music isnt configured or invalid,\n please enter his PATH : ";
		std::cin >> folderPath;
	}

    std::cout << "folder path : " << folderPath << std::endl;
	
	//Save path if not the last saved
	if (config["music-folder-path"] != folderPath)
	{
		config["music-folder-path"] = folderPath;

		std::fstream file("../Assets/config.json", std::ios::out);
		if (!file.is_open())
		{
			std::cerr << "CRITICAL ERROR : cannot open json file config file" << std::endl;
			return;
		}

		try
		{
			file << config;
		}
		catch (const std::exception& e)
		{
			std::cerr << "CRITICAL ERROR : JSON config save failed " << e.what() << std::endl;
			file.close();
			return;
		}
		file.close();
	}
	
	musicsDB.SetDB("../Assets/music.db");

	const char* sql = 
	"CREATE TABLE IF NOT EXISTS tracks ("
	"id INTEGER PRIMARY KEY,"
	"title TEXT,"
	"artist TEXT,"
	"album TEXT,"
	"path TEXT UNIQUE);";

	char* errMsg = 0;
	sqlite3_exec(musicsDB.db, sql, 0, 0, &errMsg);


	sqlite3_stmt* stmt = nullptr;
	const char* insert_sql = "INSERT OR IGNORE INTO tracks (path) VALUES (?);";

	if (sqlite3_prepare_v2(this->musicsDB.db, insert_sql, -1, &stmt, nullptr) != SQLITE_OK)
	{
		std::cerr << "Erreur prepare insert: " << sqlite3_errmsg(this->musicsDB.db) << std::endl;
	}
	else
	{
		GetFilesInFolderFunction
		(
			folderPath,
			[this, stmt](std::string path)
			{
				if (GetFileTypeEnum(path) == FileType::MUSIC)
				{
					sqlite3_reset(stmt);
					sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);

					if (sqlite3_step(stmt) != SQLITE_DONE)
					{
						std::cerr << "Erreur insert: " << sqlite3_errmsg(this->musicsDB.db) << std::endl;
					}
				}
			},
			true
		);
		sqlite3_finalize(stmt);
	}


	m_nbOfMusics = musicsDB.GetCount("SELECT COUNT(*) FROM tracks;");
	std::cout << "db size : " << m_nbOfMusics << std::endl;
}

void AudioPlayer::Update(float _dt)
{
	if (!miniAudio.MusicIsPlaying())
	{
		//Play random music
		std::vector<std::string> randomMusic;
		int randomMusicNb = rand()% m_nbOfMusics -1;
		std::cout << "random music : " << randomMusicNb;
		musicsDB.GetColumn("SELECT path FROM tracks WHERE id = " + std::to_string(randomMusicNb)+ ";", randomMusic);

		miniAudio.PlayMusic(randomMusic[0].c_str());
		randomMusic.clear();
	}
}