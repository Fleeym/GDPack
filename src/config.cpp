#include "config.hpp"

Config::Config(std::string& filename) {
    m_filename = filename;
    if(fileExists()) {
        std::ifstream config(filename);
        if(!config) {
            std::cerr << "[ERROR]: Error opening the config file in the config constructor\n";
            return;
        }
        read();

    }
}

Config::Config(Config& config) {
    m_json = config.m_json;
    m_filename = config.m_filename;
    m_geometryDashPath = config.m_geometryDashPath;
    m_packsPath = config.m_packsPath;
}

bool Config::fileExists() {
    if(fs::exists(m_filename))
        return true;
    return false;
}

bool Config::read() {
    if(!fileExists()) {
        std::cerr << "[ERROR]: File does not exist, cannot read it\n";
        return false;
    }
    std::ifstream configFile(m_filename);
    configFile >> m_json;
    configFile.close();
    m_geometryDashPath = m_json["geometryDashPath"];
    m_packsPath = m_json["packsPath"];
    m_activePack = m_json["activePack"];
    return true;
}

void Config::save() {
    m_json["packsPath"] = m_packsPath;
    m_json["geometryDashPath"] = m_geometryDashPath;
    m_json["activePack"] = m_activePack;

    std::ofstream out(m_filename);
    if (!out) {
        std::cerr << "[ERROR]: Failed to open config file while saving\n";
        return;
    }
    out << m_json;
    out.close();
}

void Config::print() {
    std::cout << std::setw(4) << m_json;
}

void Config::setActivePack(std::string& name) {
    m_activePack = name;
}

void Config::setPacksPath(std::string& path) {
    m_packsPath = path;
}

void Config::setGeometryDashPath(std::string& path) {
    m_geometryDashPath = path;
}

std::string Config::getGeometryDashPath() {
    return m_geometryDashPath;
}

std::string Config::getPacksPath() {
    return m_packsPath;
}

std::string Config::getActivePack() {
    return m_activePack;
}