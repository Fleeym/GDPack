#include "packman.hpp"

void PackManager::init(const std::string& packName, const std::string& packPath) {
    m_settings["name"] = packName;
    m_settings["path"] = packPath;
    m_manifestPath = m_settings["path"] + "/manifest.json";
    if(manifestExists()) {
#ifdef _DEBUG
        fmt::print(fg(fmt::color::light_green), "[DEBUG]: ");
        fmt::print("Found manifest.json for {}\n", m_settings["name"]);
#endif
        readManifest();
    } else {
#ifdef _DEBUG
        fmt::print(fg(fmt::color::light_green), "[DEBUG]: ");
        fmt::print("manifest.json doesn't exist for {}, creating basic manifest.json!\n", m_settings["name"]);
#endif
        createManifest();
    }
}

void PackManager::readManifest() {
    std::ifstream input(m_manifestPath);
    input >> m_json;  
    input.close();
    try {
        m_settings["name"] = m_json["name"];
        m_settings["author"] = m_json["author"];
        m_settings["description"] = m_json["description"];
        m_settings["version"] = m_json["version"];
        m_settings["gdVersion"] = m_json["gdVersion"];
        m_settings["path"] = m_json["path"];
        
    } catch (std::exception e) {
        fmt::print(fg(fmt::color::red), "[ERROR]: ");
        fmt::print("Error while reading {} manifest.json: {}\n", m_settings["name"], e.what());
    }
}

bool PackManager::manifestExists() {
    std::ifstream manifest(m_manifestPath);

    if(!manifest)
        return false;
    
    manifest.close();
    return true;
}

json PackManager::getJson() {
    return m_json;
}

void PackManager::createManifest() {
    std::ofstream manifest(m_manifestPath);
    m_json["name"] = m_settings["name"];
    m_json["author"] = "";
    m_json["description"] = "";
    // Dummy version
    m_json["version"] = "v1.0";
    // Dummy gd version, assume the pack is for 2.113
    m_json["gdVersion"] = "2.113";
    m_json["path"] = m_settings["path"];

    if(m_settings["name"] == "vanilla") {
        m_json["author"] = "RobTopGames";
        m_json["description"] = "The default resources for Geoemtry Dash.";
    }

    manifest << m_json;

    manifest.close();
}

void PackManager::cacheFile(const std::string& fileName) {
    m_cache.push_back(fileName);
}

void PackManager::pushCache() {
    m_json["cache"] = m_cache;
    std::ofstream out(m_manifestPath);

    out << m_json;
}