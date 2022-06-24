#pragma once

#include <filesystem>
#include <string>

#include "config.hpp"
#include "packman.hpp"

namespace fs = std::filesystem;

class Switcher {
private:
    Config *m_config;
    PackManager *m_packman;
public:
    bool init(Config *config);
    void setActivePack(const std::string& packPathString, const std::string& gdResPathString, std::string& packName, bool fromRevert);
    std::string getNameFromPath(std::string& path);
    void setDefaultActivePack(std::string& name);
    fs::path createVanilla();

    ~Switcher();
};