#include "interface.hpp"

void Interface::init(Config& config, std::string& directory) {
    m_directory = directory;
    if (!config.fileExists()) {
        setup(config);
    }
    mainMenu();
}

void Interface::mainMenu() {
    char choice;
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

    config.setPacksPath(m_directory);  
    config.setGeometryDashPath(gdPath.string());
    config.save();
}