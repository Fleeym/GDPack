#pragma once

#include <iostream>
#include <filesystem>

#include "switcher.hpp"

namespace fs = std::filesystem;

class Interface {
private:
    std::string m_directory = "";
    Config *m_config;
    Switcher *m_switcher;

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    void init(Config* configObject, Switcher* switcherObject, std::string& directory);
    // Main menu loop, leads to all functions
    void mainMenu();
    // Changes current texture pack
    void listTP();
    // Reverts to vanilla textures
    void revert();
    // Starts a config setup
    void editConfig();
};