#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;
using json = nlohmann::json;

class PackManager {
private:
    // JSON file
    json m_json;

    // Settings
    std::string m_manifestPath;
    std::map<std::string, std::string> m_settings;

    std::vector<std::string> m_cache;

    // Checks if the pack is active
    bool m_isActive;

public:
    // initializer
    void init(const std::string& packName, const std::string& packPath);
    // creates a manifest.json for the pack
    void createManifest();
    // reads the manifest.json and loads it in memory
    void readManifest();
    // caches files that were copied to GD/Resources when setting the pack. 
    void cacheFile(const std::string& fileName);
    // pushes the cache in the json and manifest
    void pushCache();
    // reads the files that were cached for vanilla restoration
    std::vector<std::string> readCache();
    // checks if manifest exists
    bool manifestExists();
    
    json getJson();
};