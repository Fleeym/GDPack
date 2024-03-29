#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../utils.hpp"
#include "../colors.hpp"
#include "pack.hpp"

using json = nlohmann::json;

struct ConfigSettings {
    std::string packsPath;
    std::string geometryDashPath;
    std::string activePack;
};

class Config {
  private:
    json m_json;
    std::string m_filename;

    /* 
     * INSTALLATION PATHS
     * - basic steam install
     * - SteamLibrary in D
     * - linux
     * - linux (flatpak)
     * - mac (i hope it works)
     * INSTALLATION PATHS
    **/

    const std::vector<fs::path> m_pathsToCheck = {
        "C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash",
        "D:/SteamLibrary/steamapps/common/Geometry Dash",
        "~/.steam/steamapps/common/Geometry Dash",
        " .var/app/com.valvesoftware.Steam/data/Steam/steamapps/common/Geometry Dash",
        "~/Library/Application Support/Steam/steamapps/common/Geometry Dash"};

    std::vector<std::string> m_packPaths;
    std::vector<std::string> m_packNames;

    std::vector<Pack *> m_packs;

    ConfigSettings m_settings;

    Pack *m_activePack;

  public:
    bool init(std::string &filename);
    // Checks if the config file exists
    bool fileExists();
    // Reads the config file and turns it into a json object
    bool read();
    // Prints the config file in json format, for debugging
    void print();
    // Saves all stored settings to the config.json file
    void save();
    // First time setup, runs if config.json doesn't exist
    void setup(bool manualActivate);

    // caching system
    void checkForVanillaFiles();

    // Creates the vanilla pack on first launch
    void createVanilla();

    // Setters for settings, cringe
    void setPacksPath(const std::string &gdPath);
    void setGeometryDashPath(const std::string &path);
    void setActivePack(Pack *pack);
    void setPackPaths();
    void setPackNames(const std::vector<std::string> &packPaths);

    // Getters for settings, even more cringe
    std::string getPacksPath();
    std::string getGeometryDashPath();
    Pack *getActivePack();
    std::vector<std::string> getPackPaths();
    std::vector<std::string> getPackNames();
    std::vector<Pack *> getPacks();
};