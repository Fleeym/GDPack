#pragma once

#include <iostream>
#include <filesystem>

#include "switcher.hpp"

namespace fs = std::filesystem;

class Interface {
private:
    std::string m_directory = "";

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    void init(Config& config, std::string& directory, Switcher& switcherObject);
    // Sets up the config file, asks for location of GD
    void setup(Config& config, Switcher& switcherObject);
    // Main menu loop, leads to all functions
    void mainMenu(Config& config, Switcher& switcherObject);
    // Changes current texture pack
    void listTP(Config& config, Switcher& switcherObject);
    // Reverts to vanilla textures
    void revert();
    // Starts a config setup
    void editConfig();
};