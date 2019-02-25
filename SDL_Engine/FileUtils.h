
#if !defined(_FILEUTILS_H)
#define _FILEUTILS_H

#include <map>
#include <vector>

class FileUtils
{
  private:
    /* data */
    static FileUtils *pInstance;
    std::map<std::string, std::string> _fullPathCache;
    std::vector<std::string> _searchPathArray;
    FileUtils(/* args */);
    ~FileUtils();

  public:
    
    static FileUtils *getInstance()
    {
        if (pInstance == nullptr)
            pInstance = new FileUtils();
        return pInstance;
    }
    void purge();

    std::string fullPathForFileName(const std::string &filename);
    void addSearchPath(const std::string &path);
    bool isAbsolutePath(const std::string &filename) const;
    bool isFileExist(const std::string &filename) const;

  private:
    std::string getFullPath(const std::string &filename, const std::string &path) const;
};

typedef FileUtils TheFileUtils;

#endif // _FILEUTILS_H
