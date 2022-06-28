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
    // clears the cache if Switcher detects a cache
    void clearCache();
    // gets the cache from m_cache
    std::vector<std::string> getCache();
    // checks if manifest exists
    bool manifestExists();
    // checks if the cache is empty
    bool isCacheEmpty();
    
    json getJson();
};