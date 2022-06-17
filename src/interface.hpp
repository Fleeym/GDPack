#pragma once

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Interface {
private:
    std::string m_directory = "";

public:
    // Initializes the interface and starts the first-time setup if no config file is detected
    void init(Config& config, std::string& directory);
    // Sets up the config file, asks for location of GD
    void setup(Config& config);
    // Main menu loop, leads to all functions
    void mainMenu(Config& config);
    // Changes current texture pack
    void changeTP(Config& config);
    // Reverts to vanilla textures
    void revert();
    // Starts a config setup
    void editConfig();
};