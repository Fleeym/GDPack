#pragma once

#include <filesystem>
#include <string>

#include "config.hpp"

namespace fs = std::filesystem;

class Switcher {
private:
    Config *m_config;
public:
    void init(Config *config);
    void setActivePack(const std::string& gdResPath, const std::string& packPath, const std::string& packName);
    std::string getNameFromPath(std::string& path);
    void setDefaultActivePack(std::string& name);
    void createVanilla();
};