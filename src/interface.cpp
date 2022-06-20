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
}

void Interface::mainMenu() {
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

void Interface::listTP() {
    std::cout << "Here's a list of all of your texture packs: \n\n";
    fs::path packPath = m_directory;
    std::vector<std::string> packNames;
    std::vector<std::string> packPaths;
    int dirCount = 0;

    for(auto entry : fs::directory_iterator{packPath}) {
        if(fs::is_directory(entry)) {
            // Make one array of paths of the packs, and one with just their names

            std::string entryString = entry.path().string();
            packPaths.push_back(entryString);
            entryString = entryString.substr(entryString.find_last_of('\\') + 1, (entryString.length() - entryString.find_last_of('\\')));
            packNames.push_back(entryString);
            ++dirCount;
        }
    }
    std::cout << "You have " << dirCount << " texture packs\n";
    int i = 1;
    for(auto pack : packNames) {
        if(m_config->getActivePack() == pack) {
            std::cout << "[Active] " << i << ") " << pack << '\n';
        } else {
            std::cout << i << ") " << pack << "\n";
        }
        ++i;
    }
    int choice;
    std::cout << "Choose a pack to swap (press any other key to return to the menu): ";
    std::cin >> choice;
    if(choice <= dirCount && choice > 0) {
        m_switcher->setActivePack(packPaths.at(choice - 1), m_config->getGeometryDashPath());
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
    fmt::print(fg(fmt::color::orange), "This is the help dialogue. Here is a list of possible commands: \n");
    fmt::print(fg(fmt::color::coral),
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