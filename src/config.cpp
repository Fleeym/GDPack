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
    return true;
}

void Config::print() {
    std::cout << std::setw(4) << m_json;
}

void Config::setPacksPath(std::string& path) {
    m_packsPath = path;
}

void Config::setGeometryDashPath(std::string& path) {
    m_geometryDashPath = path;
}

void Config::save() {
    m_json["packsPath"] = m_packsPath;
    m_json["geometryDashPath"] = m_geometryDashPath;

    std::ofstream out(m_filename);
    if (!out) {
        std::cerr << "[ERROR]: Failed to open config file while saving\n";
        return;
    }
    out << m_json;
    out.close();
}