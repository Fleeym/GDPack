#include "interface.hpp"

void Interface::init(Config& config, std::string& directory) {
    m_directory = directory;
    if (!config.fileExists()) {
        setup(config);
    }
    mainMenu();
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
            case 1: changeTP(); break;
            case 2: revert(); break;
            case 3: editConfig(); break;
            default: exit = true; break;
        }
    }
}

void Interface::changeTP() {
    std::cout << "Here's a list of all of your texture packs: \n\n";
    fs::path packPath = m_directory;
    std::vector<std::string> packNames;
    int dirCount = 0;

    for(auto entry : fs::directory_iterator{packPath}) {
        if(fs::is_directory(entry)) {
            std::string entryString = entry.path().string();
            entryString = entryString.substr(entryString.find_last_of('\\') + 1, (entryString.length() - entryString.find_last_of('\\')));
            packNames.push_back(entryString);
            ++dirCount;
        }
    }
    int i = 1;
    for(auto pack : packNames) {
        std::cout << i << ") " << pack << "\n";
        ++i;
    }
}

void Interface::revert() {

}

void Interface::editConfig() {

}

void Interface::setup(Config& config) {
    std::string input;
    fs::path gdPath;

    std::cout << "\nGDPack CLI\n\n"
                "[WARNING]: GDPack should be placed in an empty folder, if GDPack isn't in an empty folder, please move it.\n\n"
                "Couldn't find a config file. Setting up GDPack...\n";

    bool ok = false;
    while(ok == false) {
        std::cout << "Enter your Geometry Dash folder path (Paste with CTRL + SHIFT + V): ";
        std::getline(std::cin, input);
        gdPath = input;

        if(!fs::exists(gdPath)) {
            std::cerr << "[ERROR]: Not a valid path. Try again.\n";
            continue;
        }
        ok = true;
    }

    std::string defaultPack = "vanilla";

    config.setActivePack(defaultPack);
    config.setPacksPath(m_directory);  
    config.setGeometryDashPath(gdPath.string());
    config.save();
}