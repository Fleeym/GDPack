#pragma once

#include <iostream>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/color.h>

#include "switcher.hpp"
#include "packman.hpp"

namespace fs = std::filesystem;

class Interface {
private:
    std::string m_directory;
    Config *m_config;
    Switcher *m_switcher;

    // colors
    const fmt::color DEBUG_COLOR = fmt::color::light_green;
    const fmt::color ERROR_COLOR = fmt::color::red;
    const fmt::color VERSION_COLOR = fmt::color::medium_purple;
    const fmt::color TITLE_COLOR = fmt::color::yellow;
    const fmt::color INFO_COLOR = fmt::color::orange;
    const fmt::color PROP_COLOR = fmt::color::green_yellow;

    PackManager* m_activePack;

    std::vector<PackManager*> m_packs;

    std::vector<std::string> m_packPaths;
    std::vector<std::string> m_packNames;
    std::string m_programVersion = "1.2.0-dev";

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    bool init(Config* configObject, Switcher* switcherObject, std::string& directory);
    // Searches and lists texture packs in parent dir
    void listTP(const std::string& argument);
    // Reverts to vanilla textures
    void revert(bool);
    // Shows the help dialogue
    void showHelp(std::string& version);
    // Shows help for a specified command
    void showCommandHelp(const std::string& command);
    // sets the pack lol
    void setPack(const std::string& indexStr);

    // Gets the active pack name from config.json and saves the pack in a PackManager object
    void getActivePack();

    //getter
    std::string& getProgramVersion();

    //setter
    void setPackPaths(const std::vector<std::string> packPaths);
    void setPackNames(const std::vector<std::string> packNames);

    std::vector<PackManager*> getPacks();

    ~Interface();
};