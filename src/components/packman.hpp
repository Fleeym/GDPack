#pragma once

#include <filesystem>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>

#include "../types/colors.hpp"
#include "../types/packageSettings.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class PackManager {
  private:
    // JSON file
    json m_json;
    json m_cacheJson;

    // Settings
    std::string m_manifestPath;
    fs::path m_cachePath;
    PackageSettings m_settings;

    std::vector<std::string> m_cache;

    // Checks if the pack is active
    bool m_isActive;

  public:
    // initializer
    void init(const std::string &packName, const std::string &packPath);
    // creates a manifest.json for the pack
    void createManifest();
    // reads the manifest.json and loads it in memory
    void readManifest();
    // caches files that were copied to GD/Resources when setting the pack.
    void cacheFile(const std::string &fileName);
    // pushes the cache in the json and manifest
    void pushCache();
    // clears the cache if Switcher detects a cache
    void clearCache();
    // gets the cache from m_cache
    std::vector<std::string> getCache();
    // checks if manifest exists
    bool manifestExists();
    // saves values to manifest
    void writeManifest();
    // checks if the cache is empty
    bool isCacheEmpty();
    // checks if manifest values are the same as the stored ones
    void checkManifest();

    json getJson();
    PackageSettings &getPackInfo();
};