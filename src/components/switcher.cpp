#include "switcher.hpp"

bool Switcher::init(Config *config) {
    m_config = config;
    if (!m_config)
        return false;
    return true;
}

// Future me, I am so, so terribly sorry for this pestilence that I have
// inflicted upon you. I only hope you have the mercy to gaze in the mirror
// after rewatching this disaster of a function. Also sorry for playing hot
// potato with object references, I should have used pointers lol nevermind i
// made it ok
void Switcher::setActivePack(Pack *pack, bool fromRevert) {
    std::string gdResPathString = m_config->getGeometryDashPath();
    std::string packPathString = pack->getJson()["path"];
    std::string packName = pack->getJson()["name"];

    std::string separator = "/";

#if defined(_WIN32)
    separator = "\\";
#endif

    std::string packPathFilesString = packPathString + separator + "Resources";
    std::string gdResPathFilesString = gdResPathString + "Resources";

    if (!fs::exists(packPathFilesString)) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Resources folder not detected in pack folder, check the "
                   "pack's folder structure.\n");
        return;
    }

    // Paths to <pack>/Resources, and GD/Resources respectively
    fs::path gdResPathFiles = gdResPathFilesString;
    fs::path packPathFiles = packPathFilesString;

    // Paths to root folder of pack and GD folder
    fs::path packPath = packPathString;
    fs::path gdResPath = gdResPathString;

    std::vector<std::string> filesToCopy;

    const auto copyOptions =
        fs::copy_options::overwrite_existing | fs::copy_options::recursive;

    if (!pack->isCacheEmpty() && packName != "vanilla") {
#ifndef __optimize__
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("Cache detected, clearing cache\n");
#endif
        pack->clearCache();
    }

    // Iterate in the texture pack folder and remember which files to move
    auto iterator = fs::directory_iterator(packPathFiles);
    for (auto file : iterator) {
        std::string tempStr = file.path().string();
        std::string fileName = getNameFromPath(tempStr);
        if (packName == "vanilla" &&
            m_config->getActivePack()->getJson()["name"] != "vanilla") {
            std::vector<std::string> cache =
                m_config->getActivePack()->getCache();
            for (auto file : cache) {
                if (file == fileName) {
                    filesToCopy.push_back(fileName);
#ifndef __optimize__
                    fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
                    fmt::print("Adding {} to cache\n", fileName);
#endif
                }
            }
        } else {
            filesToCopy.push_back(fileName);
        }
        if (packName != "vanilla")
            pack->cacheFile(fileName);
    }

    if (filesToCopy.size() == 0) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("No files detected in pack Resources folder.\n");
        return;
    }

    std::string vanillaPathStr;

    if (m_config->getActivePack()->getJson()["name"] == "vanilla") {
        vanillaPathStr = m_config->getActivePack()->getJson()["path"];
        vanillaPathStr += separator + "Resources";
        if (vanillaPathStr.at(vanillaPathStr.length() - 1) ==
            separator.c_str()[0])
            vanillaPathStr.pop_back();
    }
    iterator = fs::directory_iterator(gdResPathFiles);
    for (auto file : iterator) {
        std::string fileName = getNameFromPath(file.path().string());
        auto neededFile =
            std::find(filesToCopy.begin(), filesToCopy.end(), fileName);
        if (neededFile != std::end(filesToCopy)) {
            // Move original files to vanilla pack
            if (m_config->getActivePack()->getJson()["name"] == "vanilla") {
                std::string destinationString =
                    vanillaPathStr + separator + fileName;
                fs::path destination = destinationString;
                if (!fs::exists(destination))
                    fs::copy(file.path(), destination);
            }
        }
    }
    try {
        iterator = fs::directory_iterator(gdResPathFiles);
        for (auto file : iterator) {
            std::string fileName = getNameFromPath(file.path().string());
            auto neededFile =
                std::find(filesToCopy.begin(), filesToCopy.end(), fileName);
            if (neededFile != std::end(filesToCopy)) {
                std::string originString =
                    packPathFilesString + separator + fileName;
                fs::path origin = originString;
                fs::copy(origin, file, copyOptions);
            }
        }
        m_config->setActivePack(pack);
        m_config->save();
        if (!fromRevert) {
            fmt::print(fg(SUCCESS_COLOR), "[SUCCESS]: ");
            fmt::print("Successfully switched pack to {}!\n", packName);
        }
        if (!pack->isCacheEmpty() || packName != "vanilla")
            pack->pushCache();
    } catch (fs::filesystem_error e) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("{}\n", e.what());
    }
}
std::string Switcher::getNameFromPath(const std::string &path) {
    std::string temp = path;
    char separator = '/';

#if defined(_WIN32)
    separator = '\\';
#endif
    if (temp.at(temp.length() - 1) == separator) {
        temp.pop_back();
    }

    return temp.substr(temp.find_last_of(separator) + 1,
                       (temp.length() - temp.find_last_of(separator)));
}
