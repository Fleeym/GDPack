#include "config.hpp"

Config::Config(std::string& filename) {
    m_filename = filename;
}

Config::~Config() {
    save();
}

bool Config::fileExists() {
    std::ifstream configFile (m_filename);
    if(configFile) {
        configFile.close();
        return true;
    }
    return false;
}

bool Config::read() {
    if(!fileExists()) {
        std::cerr << "ERROR: File does not exist, cannot read it\n";
        return false;
    }
    std::ifstream configFile(m_filename);
    configFile >> m_json;
    configFile.close();

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
    out << m_json;
    out.close();
}