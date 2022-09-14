#pragma once

#include <filesystem>
#include <string>
#include <algorithm>

#include "config.hpp"
#include "packman.hpp"
#include "../types/colors.hpp"

namespace fs = std::filesystem;

class Switcher
{
private:
    Config *m_config;
    std::vector<PackManager *> m_packs;

public:
    bool init(Config *config);
    void setActivePack(PackManager *pack, bool fromRevert);
    std::string getNameFromPath(const std::string &path);
    void setDefaultActivePack(const std::string &name);
};