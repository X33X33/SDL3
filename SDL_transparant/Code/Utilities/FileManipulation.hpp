#ifndef FILE_MANIPULATION_HPP
#define FILE_MANIPULATION_HPP

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

enum FileType
{
	TEXTURE,
	IMAGE,
	SOUND_BUFFER,
	MUSIC
};

//Extrude name of path
std::string GetName(std::string _string, bool _exludeType);
//Return the extension type enum
std::string GetFileType(std::string _string);
//Remove the file of his path
std::string GetPath(std::string _string);
//Change the extenssion filename
std::string ChangeType(std::string _path, std::string _newExtenssion);

std::vector<std::string> GetFilesInFolder(const std::string& folderPath);

// Check if a file exists
bool FileExist(const std::string& _path);

// Check if a folder exists
bool FolderExist(const std::string& _path);


#endif //!FILE_MANIPULATION_HPP