#include "packman.hpp"

void PackManager::init(const std::string& packName, const std::string& packPath) {
    m_packName = packName;
    m_packPath = packPath;
    m_manifestPath = m_packPath + "/manifest.json";
    if(manifestExists()) {
#ifdef DEBUG
        fmt::print("[DEBUG]: Found manifest.json for {}\n", m_packName);
#endif
        readManifest();
    } else {
#ifdef DEBUG
        fmt::print("[DEBUG]: manifest.json doesn't exist for {}, creating basic manifest.json!\n", m_packName);
#endif
        createManifest();
    }
}

void PackManager::readManifest() {
    std::ifstream input(m_manifestPath);
    input >> m_json;  
    input.close();
    try {
        m_packName = m_json["name"];
        m_author = m_json["author"];
        m_description = m_json["description"];
        m_version = m_json["version"];
        m_gdver = m_json["gdVersion"];
        m_packPath = m_json["path"];
        
    } catch (std::exception e) {
        std::cout << e.what() << '\n';
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
    m_json["name"] = m_packName;
    m_json["author"] = "";
    m_json["description"] = "";
    // Dummy version
    m_json["version"] = "v1.0";
    // Dummy gd version, assume the pack is for 2.11
    m_json["gdVersion"] = "2.113";
    m_json["path"] = m_packPath;

    if(m_packName == "vanilla") {
        m_json["author"] = "RobTopGames";
        m_json["description"] = "The default resources for Geoemtry Dash.";
    }

    manifest << m_json;

    manifest.close();
}