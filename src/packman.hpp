#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

class PackManager {
private:
    json m_json;
    std::string m_packName;
    std::string m_packPath;
    std::string m_manifestPath;
    std::string m_author;
    std::string m_gdver;
    std::string m_version;
    std::string m_description;

public:
    // initializer
    void init(const std::string& packName, const std::string& packPath);
    // creates a manifest.json for the pack
    void createManifest();
    void readManifest();
    // caches files that were copied to GD/Resources when setting the pack. 
    void cacheFiles();
    // reads the files that were cached for vanilla restoration
    std::vector<std::string> readCache();
    // checks if manifest exists
    bool manifestExists();
    
    json getJson();
};