
#include "FileManipulation.hpp"
#include <filesystem>


//Get name by full path (robust, cross-platform)
std::string GetName(std::string _string, bool _exludeType)
{
	std::filesystem::path p(_string);
	return _exludeType ? p.stem().string() : p.filename().string();
}
//Return the extension by his path, or name with extension
std::string GetFileType(std::string _string)
{
	std::filesystem::path p(_string);
	std::string ext = p.extension().string();
	if (!ext.empty() && ext[0] == '.') ext.erase(0, 1);
	return ext;
}
//Return path without name
std::string GetPath(std::string _string)
{
	std::filesystem::path p(_string);
	std::string out = p.parent_path().string();
	return out.empty() ? std::string("./") : out + "/";
}
std::string ChangeType(std::string _path, std::string _newExtenssion)
{
	std::filesystem::path p(_path);
	if (_newExtenssion.size() && _newExtenssion[0] == '.')
	p.replace_extension(_newExtenssion);
	else
	p.replace_extension("." + _newExtenssion);
	return p.string();
}


std::vector<std::string> GetFilesInFolder(const std::string& folderPath)
{
	std::vector<std::string> files;	
	
	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		if (entry.is_regular_file())
		{
			files.push_back(entry.path().string());
		}
	}
	return files;
}

bool FileExist(const std::string& _path)
{
	return std::filesystem::exists(_path) && std::filesystem::is_regular_file(_path);
}

bool FolderExist(const std::string& _path)
{
	return std::filesystem::exists(_path) && std::filesystem::is_directory(_path);
}