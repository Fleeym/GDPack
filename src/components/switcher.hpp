#pragma once

#include <algorithm>
#include <filesystem>
#include <string>

#include "../colors.hpp"
#include "config.hpp"
#include "pack.hpp"
#include "../utils.hpp"

namespace fs = std::filesystem;


class Switcher {
  private:
    Config *m_config;
    std::vector<Pack *> m_packs;

    void moveFiles(fs::path &source, fs::path &destination, std::vector<std::string> &filesToCopy);

  public:
    bool init(Config *config);
    void setActivePack(Pack *pack, bool fromRevert);
    void setDefaultActivePack(const std::string &name);
};