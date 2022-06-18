#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

using json = nlohmann::json;

class Config {
private:
    // Basic variables for functionality
    json m_json;
    std::string m_filename;
    std::string m_directory;

    // Settings
    std::map<std::string, std::string> m_settings;
    std::string m_packsPath;
    std::string m_geometryDashPath;
    std::string m_activePack;

public:
    // Constructor, gets the filename of the config file
    void init(std::string& filename, std::string& directory);
    // Checks if the config file exists
    bool fileExists();
    // Reads the config file and turns it into a json object
    bool read();
    // Prints the config file in json format, mostly for debugging
    void print();
    // Saves all stored settings to the config.json file
    void save();
    // First time setup, runs if config.json doesn't exist
    void setup();
    
    // Setters for settings, cringe
    void setPacksPath(std::string& path);
    void setGeometryDashPath(std::string& path);
    void setActivePack(std::string& name);

    // Getters for settings, even more cringe
    std::string getPacksPath();
    std::string getGeometryDashPath();
    std::string getActivePack();
};