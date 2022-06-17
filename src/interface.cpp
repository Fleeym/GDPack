#include "interface.hpp"

void Interface::init(Config& config, std::string& directory, Switcher& switcherObject) {
    m_directory = directory;
    if (!config.fileExists()) {
        setup(config, switcherObject);
    }
    mainMenu(config, switcherObject);
}

void Interface::mainMenu(Config& config, Switcher& swticherObject) {
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
            case 1: listTP(config, swticherObject); break;
            case 2: revert(); break;
            case 3: editConfig(); break;
            default: exit = true; break;
        }
    }
}

void Interface::listTP(Config& config, Switcher& switcherObject) {
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
        if(config.getActivePack() == pack) {
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
        switcherObject.setActivePack(packPaths.at(choice - 1), config.getGeometryDashPath());
    }
        
}

void Interface::revert() {

}

void Interface::editConfig() {

}

void Interface::setup(Config& config, Switcher& switcherObject) {
    std::string input;
    fs::path gdPath;

    std::cout << "\nGDPack CLI\n\n"
                "[WARNING]: GDPack should be placed in an empty folder, if GDPack isn't in an empty folder, please move it.\n\n"
                "Couldn't find a config file. Setting up GDPack...\n";

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

    switcherObject.setDefaultActivePack(defaultPack);

    config.setActivePack(defaultPack);
    config.setPacksPath(m_directory);  
    config.setGeometryDashPath(gdPath.string());
    config.save();
}