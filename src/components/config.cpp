#include "config.hpp"

bool Config::init(std::string &configFilename) {
    m_filename = configFilename;

    if (fileExists()) {
        if (!read()) {
            fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print("Error reading config.json\n");
            return false;
        }
        setPacksPath(m_settings.geometryDashPath);
        setPackPaths();
        setPackNames(m_packPaths);

        for (int i = 0; i < m_packNames.size(); i++) {
            m_packs.push_back(new Pack);
            m_packs.at(i)->init(m_packNames.at(i), m_packPaths.at(i));
            if (!m_packs.at(i))
                return false;
        }

        for (auto pack : m_packs) {
            if (pack->getPackInfo().name == m_settings.activePack) {
                setActivePack(pack);
            }
        }
    } else {
        setup(false);
    }

    return true;
}

void Config::setPackPaths() {
    fs::path packsPath = m_settings.packsPath;
    std::vector<std::string> packPaths;
    try {
        for (auto entry : fs::directory_iterator{packsPath}) {
            if (fs::is_directory(entry)) {
                std::string entryString = entry.path().string();
                packPaths.push_back(entryString);
            }
        }
    } catch (fs::filesystem_error e) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "{}.\n", e.what());
    }

    m_packPaths = packPaths;
}

void Config::setPackNames(const std::vector<std::string> &packPaths) {
    std::vector<std::string> packNames;
    char separator = '/';
#if defined(_WIN32)
    separator = '\\';
#endif
    for (auto path : packPaths) {
        std::string temp = path;
        temp = path.substr(path.find_last_of(separator) + 1,
                           (path.length() - path.find_last_of(separator)));
        packNames.push_back(temp);
    }
    m_packNames = packNames;
}

bool Config::fileExists() {
    if (fs::exists(m_filename))
        return true;
    return false;
}

bool Config::read() {
    if (!fileExists()) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("File does not exist, cannot read it\n");
        return false;
    }
    std::ifstream configFile(m_filename);
    configFile >> m_json;
    configFile.close();
    m_settings.geometryDashPath = m_json["geometryDashPath"];
    m_settings.packsPath = m_json["packsPath"];
    m_settings.activePack = m_json["activePack"];

    return true;
}

void Config::save() {
    m_json["packsPath"] = m_settings.packsPath;
    m_json["activePack"] = m_settings.activePack;
    m_json["geometryDashPath"] = m_settings.geometryDashPath;

    std::ofstream out;

    try {
        out.open(m_filename);
    } catch (std::ofstream::failure &e) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Error while saving config file!\n{}\n", e.what());
        return;
    }
    out << m_json;
    out.close();
#ifndef __optimize__
    fmt::print(fg(INFO_COLOR), "[INFO]: ");
    fmt::print("Saved config file!\n");
#endif
}

void Config::print() { std::cout << std::setw(4) << m_json; }

void Config::checkForVanillaFiles() {
    std::vector<fs::path> editedFiles;
    std::ifstream input("cache.json");
    json cacheJson;
    input >> cacheJson;
    input.close();

    fs::path gdPath = m_settings.geometryDashPath;
    gdPath.append("Resources");

    auto iterator = fs::directory_iterator(gdPath);

    for (auto file : iterator) {
        fs::path path = file.path();
        std::string fileName = getNameFromPath(path.string());
        uintmax_t fileSize = fs::file_size(path);

        if (fileSize != cacheJson[fileName]) {
            editedFiles.push_back(path);
#ifndef __optimize__
            fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
            fmt::print("Found {} with different size compared to vanilla\n",
                       fileName);
#endif
        }
    }
    if (editedFiles.size() != 0) {
        char choice;
        fmt::print(fg(INFO_COLOR), "[INFO]: ");
        fmt::print("Found {} files that are not vanilla. Do you want to create "
                   "a new pack out of them? This will allow you to delete your "
                   "Resources folder (y/n)",
                   editedFiles.size());
        std::cin >> choice;

        // ignore \n
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Config::setup(bool manualActivate) {
    std::string input;
    fs::path gdPath;

    fmt::print(fg(TITLE_COLOR), "GDPack CLI Setup\n");
    fmt::print(fg(ERROR_COLOR), "[WARNING]: ");
    fmt::print("GDPack should be placed in an empty folder, if GDPack isn't in "
               "an empty folder, please move it.\n\n");

    if (!manualActivate) {
        fmt::print(fg(INFO_COLOR), "[INFO]: ");
        fmt::print("Couldn't find a config file. Setting up GDPack...\n");
    }
    bool ok = false;

    for (auto path : m_pathsToCheck) {
        if (fs::exists(path)) {
            std::string choice = "";
            fmt::print(fg(INFO_COLOR), "[INFO]: ");
            fmt::print("Found Geometry Dash installation in: ");
            fmt::print(fg(TITLE_COLOR), "{}. ", path.string());
            fmt::print(
                "Do you want to install GDPack to that location? (Y/n): ");

            std::getline(std::cin, choice);
            if (choice == "y" || choice == "Y" || choice == "") {
                gdPath = path;
                ok = true;
            }
        }
    }

    while (ok == false) {
        fmt::print("Enter your Geometry Dash folder path (Paste with CTRL + "
                   "SHIFT + V): ");
        std::getline(std::cin, input);
        gdPath = input;

        if (!fs::exists(gdPath)) {
            fmt::print(fg(ERROR_COLOR), "\n[ERROR]: ");
            fmt::print("Not a valid path. Try again.\n");
            return;
        }
        ok = true;
    }

    setPacksPath(gdPath.string());
    setGeometryDashPath(gdPath.string());

    Pack *vanilla = new Pack;
    if (!vanilla) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Error creating the vanilla pack object\n");
        return;
    }
    createVanilla();
    fs::path vanillaPath = m_settings.packsPath;
    vanillaPath.append("vanilla");
    vanilla->init("vanilla", vanillaPath.string());
    setActivePack(vanilla);

    save();

    delete vanilla;

    fmt::print(fg(SUCCESS_COLOR), "[SUCCESS]: ");
    fmt::print("Geometry Dash installation has been set to: ");
    fmt::print(fg(TITLE_COLOR), "{}\n", gdPath.string());
}

void Config::createVanilla() {
    // Creates vanilla folder if it doesn't exist
    fs::path path = m_settings.packsPath;
    path.append("vanilla");
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }
    path.append("Resources");
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }
}

std::vector<std::string> Config::getPackPaths() { return m_packPaths; }

std::vector<std::string> Config::getPackNames() { return m_packNames; }

void Config::setActivePack(Pack *pack) {
    m_activePack = pack;
    m_settings.activePack = pack->getJson()["name"];
    save();
}

void Config::setPacksPath(const std::string &gdPath) {
    fs::path packs = gdPath;
    packs.append("gdpack");
    if (!fs::exists(packs)) {
        fs::create_directory(packs);
    }
    m_settings.packsPath = packs.string();
    save();
}

void Config::setGeometryDashPath(const std::string &path) {
    m_settings.geometryDashPath = path;
    save();
}

std::vector<Pack *> Config::getPacks() { return m_packs; }

std::string Config::getGeometryDashPath() {
    return m_settings.geometryDashPath;
}

std::string Config::getPacksPath() { return m_settings.packsPath; }

Pack *Config::getActivePack() { return m_activePack; }