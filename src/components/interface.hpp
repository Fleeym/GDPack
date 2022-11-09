#pragma once

#include <filesystem>
#include <fmt/color.h>
#include <fmt/core.h>
#include <iostream>

#include "../colors.hpp"
#include "pack.hpp"
#include "switcher.hpp"

namespace fs = std::filesystem;

class Interface {
  private:
    std::string m_directory;
    Config *m_config;
    Switcher *m_switcher;

    // colors

    Pack *m_activePack;

    std::vector<Pack *> m_packs;

    std::vector<std::string> m_packPaths;
    std::vector<std::string> m_packNames;
    const std::string m_programVersion = "v2.1.0";

  public:
    // Initializes the interface and starts the first-time setup if no config
    // file is detected
    bool init(Config *configObject, Switcher *switcherObject,
              std::string &directory);
    // Searches and lists texture packs in parent dir
    void listTP(const std::string &argument);
    // Reverts to vanilla textures
    void revert(bool);
    // Shows the help dialogue
    void showHelp(std::string &version);
    // Shows help for a specified command
    void showCommandHelp(const std::string &command);
    // sets the pack lol
    void setPack(const std::string &indexStr);

    // Gets the active pack name from config.json and saves the pack in a
    // PackManager object
    void getActivePack();

    // getter
    std::string &getProgramVersion();

    // setter
    void setPackPaths(const std::vector<std::string> packPaths);
    void setPackNames(const std::vector<std::string> packNames);

    std::vector<Pack *> getPacks();

    ~Interface();
};