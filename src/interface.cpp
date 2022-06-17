#include "interface.hpp"

void Interface::init(Config& config) {
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
                    "Press any other key to exit\n";
    while (exit != true) {
        std::cout << ">> ";
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

    std::cout << "GDPack CLI\n\n"
                "Couldn't find a config file. Setting up GDPack...\n"
                "Enter your Geometry Dash folder path: ";
    std::getline(std::cin, input);
    gdPath = input;
    config.setGeometryDashPath(gdPath.string());
    config.save();
}