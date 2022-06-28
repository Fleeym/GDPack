#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "packman.hpp"

using json = nlohmann::json;

class Config {
private:
    // Basic variables for functionality
    json m_json;
    std::string m_filename;
    std::string m_directory;

    std::vector<std::string> m_packPaths;
    std::vector<std::string> m_packNames;

    std::vector<PackManager*> m_packs;

    // Settings
    std::map<std::string, std::string> m_settings;

    PackManager* m_activePack;

public:
    // Constructor, gets the filename of the config file
    bool init(std::string& filename, std::string& directory);
    // Checks if the config file exists
    bool fileExists();
    // Reads the config file and turns it into a json object
    bool read();
    // Prints the config file in json format, mostly for debugging
    void print();
    // Saves all stored settings to the config.json file
    void save();
    // First time setup, runs if config.json doesn't exist
    void setup(bool manualActivate);

    // Creates the vanilla pack on first launch
    void Config::createVanilla();
    
    // Setters for settings, cringe
    void setPacksPath(std::string& path);
    void setGeometryDashPath(std::string& path);
    void setActivePack(PackManager *pack);
    void setPackPaths();
    void setPackNames(const std::vector<std::string>& packPaths);
    
    // Getters for settings, even more cringe
    std::string getPacksPath();
    std::string getGeometryDashPath();
    PackManager* getActivePack();
    std::vector<std::string> getPackPaths();
    std::vector<std::string> getPackNames();
    std::vector<PackManager*> getPacks();
};