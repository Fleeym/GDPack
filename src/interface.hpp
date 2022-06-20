#pragma once

#include <iostream>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/color.h>

#include "switcher.hpp"

namespace fs = std::filesystem;

class Interface {
private:
    std::string m_directory;
    Config *m_config;
    Switcher *m_switcher;
    std::string m_programVersion = "0.0.1";

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    void init(Config* configObject, Switcher* switcherObject, std::string& directory);
    // Main menu loop, leads to all functions
    void mainMenu();
    // Searches and lists texture packs in parent dir
    void listTP();
    // Reverts to vanilla textures
    void revert();
    // Starts a config setup
    void editConfig();
    // Shows the help dialogue
    void showHelp(std::string& version);

    //getter
    std::string& getProgramVersion();
};