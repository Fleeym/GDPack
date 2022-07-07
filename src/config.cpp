#include "config.hpp"

bool Config::init(std::string& filename, std::string& directory) {
    m_filename = filename;
    m_directory = directory;

    setPackPaths();
    setPackNames(m_packPaths);

    for(int i = 0; i < m_packNames.size(); i++) {
        m_packs.push_back(new PackManager);
        m_packs.at(i)->init(m_packNames.at(i), m_packPaths.at(i));
        if(!m_packs.at(i)) return false;
    }

    if(fileExists()) {
        // At initialization, read the config file and store it in the local variables, so no data is lost if you launch the program multiple times
        if(!read()) {
            fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print("Error reading config.json\n");
            return false;
        }
        setPacksPath(m_directory);
    } else {
        setup(false);
    }

    return true;
}

void Config::setPackPaths(){
    fs::path packsPath = m_directory;
    std::vector<std::string> packPaths;

    for(auto entry : fs::directory_iterator{packsPath}) {
        if(fs::is_directory(entry)) {
            // Make one array of paths of the packs, and one with just their names

            std::string entryString = entry.path().string();
            packPaths.push_back(entryString);
        }
    }
    m_packPaths = packPaths;
}

void Config::setPackNames(const std::vector<std::string>& packPaths) {
    std::vector<std::string> packNames;
    for(auto path : packPaths) {
        if(packPaths[packPaths.size() - 1] == "\\") {
            packNames.pop_back();
        }
        std::string temp = path;
        temp = path.substr(path.find_last_of('\\') + 1, (path.length() - path.find_last_of('\\')));
        packNames.push_back(temp);
    }
    m_packNames = packNames;
}

bool Config::fileExists() {
    if(fs::exists(m_filename))
        return true;
    return false;
}

bool Config::read() {
    if(!fileExists()) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("File does not exist, cannot read it\n");
        return false;
    }
    std::ifstream configFile(m_filename);
    configFile >> m_json;
    configFile.close();
    m_settings["geometryDashPath"] = m_json["geometryDashPath"];
    m_settings["packsPath"] = m_json["packsPath"];
    m_settings["activePack"] = m_json["activePack"];

    PackManager* activePack;
    for(auto pack : m_packs) {
        if(pack->getJson()["name"] == m_settings["activePack"])
            activePack = pack;
    }

    m_activePack = activePack;
    return true;
}

void Config::save() {
    m_json["packsPath"] = m_settings["packsPath"];
    m_json["geometryDashPath"] = m_settings["geometryDashPath"];
    m_json["activePack"] = m_settings["activePack"];
    
    std::ofstream out(m_filename);      
    if (!out) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Error while saving config file.\n");
        return;
    }
    out << m_json;
    out.close();
    
}

void Config::print() {
    std::cout << std::setw(4) << m_json;
}

void Config::checkForVanillaFiles() {
    std::vector<fs::path> editedFiles;
    std::ifstream input("cache.json");
    json cacheJson;
    input >> cacheJson;
    input.close();

    fs::path gdPath = m_settings["geometryDashPath"];
    gdPath.append("Resources");

    auto iterator = fs::directory_iterator(gdPath);

    for (auto file : iterator) {
        fs::path path = file.path();
        std::string fileName = getNameFromPath(path.string());
        uintmax_t fileSize = fs::file_size(path);

        if(fileSize != cacheJson[fileName]) {
            editedFiles.push_back(path);
#ifdef _DEBUG
            fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
            fmt::print("Found {} with different size compared to vanilla\n", fileName);
#endif
        }
    }
    if(editedFiles.size() != 0) {
        char choice;
        fmt::print(fg(INFO_COLOR), "[INFO]: ");
        fmt::print("Found {} files that are not vanilla. Do you want to create a new pack out of them? This will allow you to delete your Resources folder (y/n)");
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
    fmt::print("GDPack should be placed in an empty folder, if GDPack isn't in an empty folder, please move it.\n\n");

    if(!manualActivate) {
        fmt::print(fg(INFO_COLOR), "[INFO]: ");
        fmt::print("Couldn't find a config file. Setting up GDPack...\n");
    }
    bool ok = false;
    while(ok == false) {
        fmt::print("Enter your Geometry Dash folder path (Paste with CTRL + SHIFT + V): ");
        std::getline(std::cin, input);
        gdPath = input;

        if(!fs::exists(gdPath)) {
            fmt::print(fg(ERROR_COLOR), "\n[ERROR]: ");
            fmt::print("Not a valid path. Try again.\n");
            return;
        }
        ok = true;
    }

    if(!manualActivate) {
        PackManager* vanilla = new PackManager;
        if(!vanilla) {
            fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print("Error creating the vanilla pack object\n");
            return;
        }
        createVanilla();
        std::string vanillaPath = m_directory + "\\vanilla";
        vanilla->init("vanilla", vanillaPath);
        setActivePack(vanilla);
    }
    
    setGeometryDashPath(gdPath.string());
    save();
}

void Config::createVanilla() {
    // Creates vanilla folder if it doesn't exist
    std::string vanillaStr = getPacksPath();
    vanillaStr += "\\vanilla";
    if(vanillaStr.at(vanillaStr.length() - 1) == '\\')
        vanillaStr.pop_back();

    fs::path vanillaPath = vanillaStr;
    if(!fs::exists(vanillaPath)) {
        fs::create_directory(vanillaPath);
    }
    vanillaPath.append("Resources");
    if(!fs::exists(vanillaPath)) {
        fs::create_directory(vanillaPath);
    }
}   


std::vector<std::string> Config::getPackPaths() {
    return m_packPaths;
}

std::vector<std::string> Config::getPackNames() {
    return m_packNames;
}

void Config::setActivePack(PackManager* pack) {
    m_activePack = pack;
    m_settings["activePack"] = pack->getJson()["name"];
    save();
}

void Config::setPacksPath(std::string& path) {
    m_settings["packsPath"] = path;
    save();
}

void Config::setGeometryDashPath(std::string& path) {
    m_settings["geometryDashPath"] = path;
    save();
}

std::vector<PackManager*> Config::getPacks() {
    return m_packs;
}

std::string Config::getGeometryDashPath() {
    return m_settings["geometryDashPath"];
}

std::string Config::getPacksPath() {
    return m_settings["packsPath"];
}

PackManager* Config::getActivePack() {
    return m_activePack;
}