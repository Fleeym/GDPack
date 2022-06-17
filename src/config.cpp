#include "config.hpp"

Config::Config(std::string filename) {
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

bool Config::readJson() {
    if(!fileExists())
        return false;
    std::ifstream configFile(m_filename);
    configFile >> m_json;
    configFile.close();

    return true;
}

void Config::printJson() {
    std::cout << std::setw(4) << m_json;
}

void Config::writeJson() {
    std::ofstream configFile(m_filename);
    configFile << m_json;
    configFile.close();
}