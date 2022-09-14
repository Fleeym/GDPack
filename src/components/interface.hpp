#pragma once

#include <iostream>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/color.h>

#include "switcher.hpp"
#include "packman.hpp"
#include "../types/colors.hpp"

namespace fs = std::filesystem;

class Interface
{
private:
    std::string m_directory;
    Config *m_config;
    Switcher *m_switcher;

    // colors

    PackManager *m_activePack;

    std::vector<PackManager *> m_packs;

    std::vector<std::string> m_packPaths;
    std::vector<std::string> m_packNames;
    std::string m_programVersion = "1.2.0-dev";

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    bool init(Config *configObject, Switcher *switcherObject, std::string &directory);
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

    // Gets the active pack name from config.json and saves the pack in a PackManager object
    void getActivePack();

    // getter
    std::string &getProgramVersion();

    // setter
    void setPackPaths(const std::vector<std::string> packPaths);
    void setPackNames(const std::vector<std::string> packNames);

    std::vector<PackManager *> getPacks();

    ~Interface();
};