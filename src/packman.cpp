#include "packman.hpp"

void PackManager::init(const std::string& packName, const std::string& packPath) {
    m_packName = packName;
    m_packPath = packPath;
    m_manifestPath = m_packPath + "/manifest.json";
    if(manifestExists())
        fmt::print("The manifest.json path for {} is: {}\n", m_packName, m_manifestPath);
    else
        fmt::print("manifest.json doesn't exist!\n");
}

bool PackManager::manifestExists() {
    std::ofstream manifest(m_manifestPath);

    if(!manifest)
        return false;
    
    manifest.close();
    return true;
}