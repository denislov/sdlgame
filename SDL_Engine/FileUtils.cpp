#include "FileUtils.h"
#include "SDL.h"
#include <algorithm>
FileUtils *FileUtils::pInstance = nullptr;
FileUtils::FileUtils(/* args */)
{
}
FileUtils::~FileUtils()
{
    _fullPathCache.clear();
    _searchPathArray.clear();
    printf("FileUtils is released\n");
}
void FileUtils::purge()
{
    delete pInstance;
    pInstance = nullptr;
}

std::string FileUtils::fullPathForFileName(const std::string &filename)
{
    if (isAbsolutePath(filename))
        return filename;
    auto iter = _fullPathCache.find(filename);
    if (iter != _fullPathCache.end())
        return iter->second;
    std::string fullPath;

    for (auto it = _searchPathArray.begin(); it != _searchPathArray.end(); it++)
    {
        fullPath = this->getFullPath(filename, *it);

        if (fullPath.length() > 0)
        {
            _fullPathCache.insert(std::make_pair(filename, fullPath));
            return fullPath;
        }
    }
    return "";
}
void FileUtils::addSearchPath(const std::string &path)
{
    auto iter = std::find_if(_searchPathArray.begin(), _searchPathArray.end(), [path](std::string name) {
        return path == name;
    });
    if (iter == _searchPathArray.end())
        _searchPathArray.push_back(path);
}
bool FileUtils::isAbsolutePath(const std::string &filename) const
{
    return false;
}
bool FileUtils::isFileExist(const std::string &filename) const
{
    //检查是否存在
    SDL_RWops *file = SDL_RWFromFile(filename.c_str(), "r");

    if (file)
    {
        SDL_RWclose(file);
        return true;
    }
    //检查错误代码
    //printf("Error %d: Failed to open file\n", errno);
    return false;
}
std::string FileUtils::getFullPath(const std::string &filename, const std::string &path) const
{
    std::string fullPath = path + "/" + filename;
    if (isFileExist(fullPath))
        return fullPath;
    return "";
}
