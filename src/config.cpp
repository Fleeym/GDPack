#include "config.hpp"

void Config::init(std::string& filename, std::string& directory) {
    m_filename = filename;
    m_directory = directory;

    if(fileExists()) {
        std::ifstream config(filename);
        if(!config) {
            std::cerr << "[ERROR]: Error opening the config file\n";
            return;
        }
        // At initialization, read the config file and store it in the local variables, so no data is lost if you launch the program multiple times
        if(!read())
            std::cerr << "[ERROR]: Error reading config.json\n";
    } else {
        setup(false);
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
    m_settings["geometryDashPath"] = m_json["geometryDashPath"];
    m_settings["packsPath"] = m_json["packsPath"];
    m_settings["activePack"] = m_json["activePack"];
    return true;
}

void Config::save() {
    m_json["packsPath"] = m_settings["packsPath"];
    m_json["geometryDashPath"] = m_settings["geometryDashPath"];
    m_json["activePack"] = m_settings["activePack"];

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

void Config::setup(bool manualActivate) {
    std::string input;
    fs::path gdPath;

    fmt::print(fg(fmt::color::yellow), "GDPack CLI Setup\n");
    fmt::print(fg(fmt::color::red), "[WARNING]: GDPack should be placed in an empty folder, if GDPack isn't in an empty folder, please move it.\n\n");

    if(!manualActivate)
        fmt::print("Couldn't find a config file. Setting up GDPack...\n");

    bool ok = false;
    while(ok == false) {
        std::cout << "Enter your Geometry Dash RESOURCES folder path (Paste with CTRL + SHIFT + V): ";
        std::getline(std::cin, input);
        gdPath = input;

        if(!fs::exists(gdPath)) {
            std::cerr << "[ERROR]: Not a valid path. Try again.\n";
            continue;
        }
        ok = true;
    }

    std::string defaultPack = "vanilla";

    setActivePack(defaultPack);
    setPacksPath(m_directory);  
    setGeometryDashPath(gdPath.string());
    save();
}

void Config::setActivePack(std::string& name) {
    m_settings["activePack"] = name;
}

void Config::setPacksPath(std::string& path) {
    m_settings["packsPath"] = path;
}

void Config::setGeometryDashPath(std::string& path) {
    m_settings["geometryDashPath"] = path;
}

std::string Config::getGeometryDashPath() {
    return m_settings["geometryDashPath"];
}

std::string Config::getPacksPath() {
    return m_settings["packsPath"];
}

std::string Config::getActivePack() {
    return m_settings["activePack"];
}