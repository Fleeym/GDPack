#include "switcher.hpp"

bool Switcher::init(Config *config) {
    m_config = config;
    if (!m_config)
        return false;
    return true;
}

void Switcher::setActivePack(Pack *pack, bool fromRevert) {
    fs::path gdPath = m_config->getGeometryDashPath();
    fs::path packPath = pack->getPackInfo().path;

    fs::path gdResources = m_config->getGeometryDashPath();
    gdResources.append("Resources");

    fs::path packResources = pack->getPackInfo().path;
    packResources.append("Resources");

    // Name of pack that we are switching to
    std::string packName = pack->getPackInfo().name;

    if (!fs::exists(packResources)) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Resources folder not detected in pack folder, check the "
                   "pack's folder structure.\n");
        return;
    }

    std::vector<std::string> filesToCopy;

    if (!pack->isCacheEmpty() && packName != "vanilla") {
        if (Utils::isDebug()) {
            fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
            fmt::print("Cache detected, clearing cache\n");
        }
        pack->clearCache();
    }

    // Iterate in the texture pack folder and remember which files to move
    auto iterator = fs::directory_iterator(packResources);
    for (auto file : iterator) {
        std::string filePath = file.path().string();
        std::string fileName = Utils::getNameFromPath(filePath);

        // If we are reverting, also check the cache of the active pack.
        if (packName == "vanilla" && m_config->getActivePack()->getPackInfo().name != "vanilla") {
            std::vector<std::string> cache = m_config->getActivePack()->getCache();
            for (auto file : cache) {
                if (file == fileName) {
                    filesToCopy.push_back(fileName);

                    if (Utils::isDebug()) {
                        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
                        fmt::print("Adding {} to cache\n", fileName);
                    }
                }
            }
        } else {
            filesToCopy.push_back(fileName);
        }
        // If we are not reverting, cache the file.
        if (packName != "vanilla")
            pack->cacheFile(fileName);
    }

    if (filesToCopy.size() == 0) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("No files detected in pack Resources folder.\n");
        return;
    }

    // If vanilla is active, move the untouched files first.
    if (m_config->getActivePack()->getPackInfo().name == "vanilla") {
        fs::path vanillaResources = m_config->getActivePack()->getPackInfo().path;
        vanillaResources.append("Resources");

        fs::path destination = vanillaResources;
        moveFiles(gdResources, destination, filesToCopy);
    }

    // Move files from pack to GD resources
    moveFiles(packResources, gdResources, filesToCopy);

    m_config->setActivePack(pack);
    m_config->save();
    if (!fromRevert) {
        fmt::print(fg(SUCCESS_COLOR), "[SUCCESS]: ");
        fmt::print("Successfully switched pack to {}!\n", packName);
    }
    if (!pack->isCacheEmpty() || packName != "vanilla")
        pack->pushCache();
}
/**
 * Moves files in filesToCopy from source to destination
 * filesToCopy has to contain file names
**/
void Switcher::moveFiles(fs::path &source, fs::path &destination, std::vector<std::string> &filesToCopy) {
    const auto copyOptions = 
        fs::copy_options::overwrite_existing | 
        fs::copy_options::recursive;

    auto iterator = fs::directory_iterator(source);
    for (auto file : iterator) {
        std::string fileName = Utils::getNameFromPath(file.path().string());
        auto neededFile = std::find(filesToCopy.begin(), filesToCopy.end(), fileName);
        if (neededFile != std::end(filesToCopy)) {
            fs::path destinationFilename = destination;
            destinationFilename.append(fileName);

            try {
                fs::copy(file.path(), destinationFilename, copyOptions);
            } catch (fs::filesystem_error &e) {
                std::cout << e.what() << "\n";
            }
        }
    }
}