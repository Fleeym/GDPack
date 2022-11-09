#include "pack.hpp"

void Pack::init(const std::string &packName,
                       const std::string &packPath) {
    m_settings.name = packName;
    m_settings.path = packPath;
    m_cachePath = packPath;
    m_cachePath.append("cache.json");
    m_manifestPath = m_settings.path + "/manifest.json";
    if (manifestExists()) {
#ifndef __optimize__
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Found manifest.json for {}\n", m_settings.name);
#endif
        readManifest();
        checkManifest();
    } else {
#ifndef __optimize__
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("manifest.json doesn't exist for {}, creating basic "
                   "manifest.json!\n",
                   m_settings.name);
#endif
        createManifest();
    }
}

void Pack::writeManifest() {
    std::ofstream out(m_manifestPath);
    std::ofstream cacheOut(m_cachePath);
    if (!out || !cacheOut) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Failed to write to manifest.json, pack: {}\n",
                   m_settings.name);
        return;
    }
    out << m_json;
    cacheOut << m_cacheJson;
    cacheOut.close();
    out.close();
}

void Pack::checkManifest() {
    if (m_json["name"] != m_settings.name) {
#ifndef __optimize__
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Invalid name for pack {}, correcting manifest.json\n",
                   m_settings.name);
#endif
        m_json["name"] = m_settings.name;
        writeManifest();
    }
    if (m_json["path"] != m_settings.path) {
#ifndef __optimize__
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Invalid path for pack {}, correcting manifest.json\n",
                   m_settings.name);
#endif
        m_json["path"] = m_settings.path;
        writeManifest();
    }
}

void Pack::readManifest() {
    std::ifstream input(m_manifestPath);
    input >> m_json;
    input.close();

    // if no cache found, just create an empty file.
    if (!fs::exists(m_cachePath) && m_settings.name != "vanilla") {
        std::ofstream cache(m_cachePath);
        cache << "[]";
        cache.close();
    }

    if (m_settings.name != "vanilla") {
        std::ifstream cacheInput(m_cachePath);
        try {
            cacheInput >> m_cacheJson;\
        } catch (nlohmann::json::exception &e) {
            std::cout << e.what() << "\n";
        }
        cacheInput.close();
    }

    try {
        m_settings.author = m_json["author"];
        m_settings.description = m_json["description"];
        m_settings.version = m_json["version"];
        m_settings.gdVersion = m_json["gdVersion"];

        for (int i = 0; i < m_cacheJson.size(); i++) {
            std::string temp = m_cacheJson[i];
            m_cache.push_back(temp);
        }
    } catch (const std::exception &e) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Error while reading {} manifest.json: {}\n",
                   m_settings.name, e.what());
    }
}

std::vector<std::string> Pack::getCache() { return m_cache; }

bool Pack::manifestExists() {
    std::ifstream manifest(m_manifestPath);

    if (!manifest)
        return false;

    manifest.close();
    return true;
}

void Pack::clearCache() { m_cache.clear(); }

bool Pack::isCacheEmpty() {
    if (m_cache.size() == 0)
        return true;
    return false;
}

json Pack::getJson() { return m_json; }

PackageSettings &Pack::getPackInfo() { return m_settings; };

void Pack::createManifest() {
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

void Pack::cacheFile(const std::string &fileName) {
    m_cache.push_back(fileName);
}

void Pack::pushCache() {
    m_cacheJson = m_cache;
    writeManifest();
}