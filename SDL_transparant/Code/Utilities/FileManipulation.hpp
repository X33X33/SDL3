#ifndef FILE_MANIPULATION_HPP
#define FILE_MANIPULATION_HPP

#include <vector>
#include <string>
//#include <functional>
#include <filesystem>

enum FileType
{
	TEXTURE,
	IMAGE,
	SOUND_BUFFER,
	MUSIC,
	UNKNOW
};

//Extrude name of path
std::string GetName(std::string _string, bool _exludeType);
//Return the extension type enum
std::string GetFileType(std::string _string);
//Get file type
//CURRENTLY SUPPORTED : image and music (not a lot of format, personal usage only)
FileType GetFileTypeEnum(std::string _string);
//Remove the file of his path
std::string GetPath(std::string _string);
//Change the extenssion filename
std::string ChangeType(std::string _path, std::string _newExtenssion);

// \brief Get files on folder
//
// \param the path of your folder
// \param the vector for return files
// \param set to true if you want parse folder in the folder
void GetFilesInFolder(const std::string& folderPath, std::vector<std::string>& _return, bool _recursif = false);

//Parse folder and return result to custom function
//Use this if you dindt want use vector
//Usefull if you have really large scan to do, like scan to create DB :)
template <typename Function>
void GetFilesInFolderFunction(const std::string& folderPath, Function _function, bool _recursif = false)
{
	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            _function(entry.path().string());
        }
        else if (_recursif && entry.is_directory())
        {
            GetFilesInFolderFunction(entry.path().string(), _function, _recursif);
        }
    }
}


// Check if a file exists
bool FileExist(const std::string& _path);

// Check if a folder exists
bool FolderExist(const std::string& _path);


#endif //!FILE_MANIPULATION_HPP