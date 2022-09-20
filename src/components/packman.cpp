#include "packman.hpp"

void PackManager::init(const std::string &packName,
                       const std::string &packPath) {
    m_settings.name = packName;
    m_settings.path = packPath;
    m_manifestPath = m_settings.path + "/manifest.json";
    if (manifestExists()) {
#ifdef _DEBUG
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Found manifest.json for {}\n", m_settings.name);
#endif
        readManifest();
        checkManifest();
    } else {
#ifdef _DEBUG
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("manifest.json doesn't exist for {}, creating basic "
                   "manifest.json!\n",
                   m_settings.name);
#endif
        createManifest();
    }
}

void PackManager::writeManifest() {
    std::ofstream out(m_manifestPath);
    if (!out) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Failed to write to manifest.json, pack: {}\n",
                   m_settings.name);
        return;
    }
    out << m_json;
    out.close();
}

void PackManager::checkManifest() {
    if (m_json["name"] != m_settings.name) {
#ifdef _DEBUG
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Invalid name for pack {}, correcting manifest.json\n",
                   m_settings.name);
#endif
        m_json["name"] = m_settings.name;
        writeManifest();
    }
    if (m_json["path"] != m_settings.path) {
#ifdef _DEBUG
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Invalid path for pack {}, correcting manifest.json\n",
                   m_settings.name);
#endif
        m_json["path"] = m_settings.path;
        writeManifest();
    }
}

void PackManager::readManifest() {
    std::ifstream input(m_manifestPath);
    input >> m_json;
    input.close();
    try {
        m_settings.author = m_json["author"];
        m_settings.description = m_json["description"];
        m_settings.version = m_json["version"];
        m_settings.gdVersion = m_json["gdVersion"];

        for (int i = 0; i < m_json["cache"].size(); i++) {
            std::string temp = m_json["cache"][i];
            m_cache.push_back(temp);
        }
    } catch (const std::exception &e) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Error while reading {} manifest.json: {}\n",
                   m_settings.name, e.what());
    }
}

std::vector<std::string> PackManager::getCache() { return m_cache; }

bool PackManager::manifestExists() {
    std::ifstream manifest(m_manifestPath);

    if (!manifest)
        return false;

    manifest.close();
    return true;
}

void PackManager::clearCache() { m_cache.clear(); }

bool PackManager::isCacheEmpty() {
    if (m_cache.size() == 0)
        return true;
    return false;
}

json PackManager::getJson() { return m_json; }

PackageSettings &PackManager::getPackInfo() { return m_settings; };

void PackManager::createManifest() {
    m_json["name"] = m_settings.name;
    m_json["author"] = "";
    m_json["description"] = "";
    // Dummy version
    m_json["version"] = "1.0.0";
    // Dummy gd version, assume the pack is for 2.113
    m_json["gdVersion"] = "2.1";
    m_json["path"] = m_settings.path;

    if (m_settings.name == "vanilla") {
        m_json["author"] = "RobTopGames";
        m_json["description"] = "The default resources for Geoemtry Dash.";
    }

    writeManifest();
}

void PackManager::cacheFile(const std::string &fileName) {
    m_cache.push_back(fileName);
}

void PackManager::pushCache() {
    m_json["cache"] = m_cache;
    writeManifest();
}