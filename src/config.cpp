#include "config.hpp"

Config::Config(std::string& filename) {
    m_filename = filename;
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

void Config::write() {
    std::ofstream configFile(m_filename);
    configFile << m_json;
    configFile.close();
}

void Config::setPacksLocation(std::string& path) {
    m_json["packsPath"] = path;
}