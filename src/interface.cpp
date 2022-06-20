#include "interface.hpp"

/*void Interface::init(Config& config, std::string& directory, Switcher& switcherObject) {
    m_directory = directory;
    if (!config.fileExists()) {
        setup(config, switcherObject);
    }
    mainMenu(config, switcherObject);
}*/

void Interface::init(Config* configObject, Switcher* switcherObject, std::string& directory) {
    m_directory = directory;
    m_config = configObject;
    m_switcher = switcherObject;

    if(!m_config->fileExists()) {
        m_config->setup(false);
    }

    m_packPaths = getPackPaths();
    m_packNames = getPackNames(m_packPaths);
}

void Interface::mainMenu() { // legacy
    int choice;
    bool exit = false;
    std::cout << "GDPack CLI\n"
                    "1) Change active texture pack\n"
                    "2) Revert to vanilla\n"
                    "3) Edit config\n"
                    "Press any other key to exit\n\n";
    while (exit != true) {
        std::cout << "GDPack >> ";
        std::cin >> choice;
        switch(choice) {
            case 1: listTP(); break;
            case 2: revert(); break;
            case 3: editConfig(); break;
            default: exit = true; break;
        }
    }
}

std::vector<std::string> Interface::getPackPaths(){
    fs::path packsPath = m_directory;
    std::vector<std::string> packPaths;

    for(auto entry : fs::directory_iterator{packsPath}) {
        if(fs::is_directory(entry)) {
            // Make one array of paths of the packs, and one with just their names

            std::string entryString = entry.path().string();
            packPaths.push_back(entryString);
        }
    }
    return packPaths;
}

std::vector<std::string> Interface::getPackNames(const std::vector<std::string>& packPaths) {
    std::vector<std::string> packNames;
    for(auto path : packPaths) {
        if(packPaths[packPaths.size() - 1] == "\\") {
            packNames.pop_back();
        }
        std::string temp = path;
        temp = path.substr(path.find_last_of('\\') + 1, (path.length() - path.find_last_of('\\')));
        packNames.push_back(temp);
    }
    return packNames;
}

void Interface::listTP() {
    fmt::print(fg(fmt::color::yellow), "GDPack CLI ");
    fmt::print(fg(fmt::color::purple), "v{}\n", m_programVersion);
    fmt::print(fg(fmt::color::orange), "Here's a list of all of your texture packs: \n\n");
    
    int i = 1;
    for(auto pack : m_packNames) {
        if(m_config->getActivePack() == pack) {
            std::cout << i << ") " << pack << "[*]" << '\n';
        } else {
            std::cout << i << ") " << pack << "\n";
        }
        ++i;
    }
}

void Interface::setPack(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    if(index <= m_packPaths.size() && index > 0) {
        m_switcher->setActivePack(m_packPaths.at(index - 1), m_config->getGeometryDashPath(), m_packNames.at(index - 1));
    }
}

void Interface::revert() {

}

void Interface::editConfig() {

}

void Interface::showHelp(std::string& version) {
    fmt::print(fg(fmt::color::yellow), "GDPack ");
    fmt::print(fg(fmt::color::purple), "v{}", version);
    fmt::print(" [COMMAND] [VALUE]\n"
                "The CLI Geometry Dash texture pack manager!\n\n");
    fmt::print(fg(fmt::color::orange), "Here is a list of possible commands: \n");
    fmt::print(fg(fmt::color::cyan),
        " * help -> Shows this dialogue. Can also be used as an argument for the other commands.\n"
        " * setup -> Repeats the first-run setup.\n"
        " * list -> Lists all installed packs.\n"
        " * revert -> Reverts the game to vanilla resources.\n"
        " * set [PACK] -> Sets the active pack.\n"
        " * config [OPTION] [VALUE] -> Edits the settings from the config file.\n"
    );
}

std::string& Interface::getProgramVersion() {
    return m_programVersion;
}

void Interface::setPackPaths(const std::vector<std::string> packPaths) {
    m_packPaths = packPaths;
}

void Interface::setPackNames(const std::vector<std::string> packNames) {
    m_packNames = packNames;
}