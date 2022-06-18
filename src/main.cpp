#include "config.hpp"
#include "interface.hpp"
#include "switcher.hpp"

#include <vector>

// First, ask for the paths and Geometry Dash location if this is the first run.
// If this isn't the first run, show the options menu:
// Show how many packs are present, remember active texture pack
// 1) Change active texture pack
// 2) Revert to vanilla (if vanilla folder is present in the packs folder and has files)
// 3) Edit config file
// 4) Exit program

int getCommand(std::string& name, std::vector<std::string>& commands) {
    for (auto i = 0; i < commands.size() - 1; i++) {
        if(commands[i] == name)
            return i;
    }
    return -1;
}

int main(int argc, char **argv) {
    // Sets working directory to application folder, used to set config filepath
    std::string directory = argv[0];
    directory.erase(directory.find_last_of('\\')+ 1);
    std::string filename = directory + "config.json";

    std::vector<std::string> commandOptions = {"help", "config", "setup", "set", "revert"};

    // Initialize components
    Config* configObject = new Config;
    Interface* interfaceObject = new Interface;
    Switcher* switcherObject = new Switcher;

    configObject->init(filename, directory);
    switcherObject->init(configObject);
    interfaceObject->init(configObject, switcherObject, directory);

    switch(argc) {
        case 1: break; // go to help
        case 2: break;
    }

    delete configObject;
    delete interfaceObject;
    delete switcherObject;

    return 0;
}