#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Switcher {
private:
    std::string m_activePack;
public:
    Switcher(std::string& activePack);
    void setActivePack(std::string& packPath, std::string& resPath);
    std::string getNameFromPath(std::string& path);
    void setDefaultActivePack(std::string& name);
};