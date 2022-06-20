#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Switcher {
private:
    Config *m_config;
public:
    void init(Config *config);
    void setActivePack(std::string& packPath, std::string& resPath);
    std::string getNameFromPath(std::string& path);
    void setDefaultActivePack(std::string& name);
    void createVanilla();
};