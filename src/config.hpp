#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class Config {
private:
    // Basic variables for functionality
    json m_json;
    std::string m_filename = "";

    // Settings
    std::string m_packsPath = "";
    std::string m_geometryDashPath = "";
    bool firstRun = true;

public:
    // Constructor, gets the filename of the config file
    Config(std::string& filename);
    // Checks if the config file exists
    bool fileExists();
    // Reads the config file and turns it into a json object
    bool read();
    void print(); // testing
    // Saves all stored settings to the config.json file
    void save();
    
    // Setters for settings, cringe
    void setPacksPath(std::string& path);
    void setGeometryDashPath(std::string& path);
};