#pragma once

#include <filesystem>
#include <string>
#include <algorithm>

#include "config.hpp"
#include "packman.hpp"

namespace fs = std::filesystem;

class Switcher {
private:
    Config *m_config;
    std::vector<PackManager*> m_packs;
public:
    bool init(Config *config);
    void setActivePack(PackManager* pack, bool fromRevert);
    std::string getNameFromPath(std::string& path);
    void setDefaultActivePack(std::string& name);
};