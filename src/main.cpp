#include "config.hpp"
#include "interface.hpp"
#include "switcher.hpp"

#include <vector>

int getCommand(std::string&, std::vector<std::string>&);
void selectCommand(Interface* interfaceObject, int argc);

// First, ask for the paths and Geometry Dash location if this is the first run.
// If this isn't the first run, show the options menu:
// Show how many packs are present, remember active texture pack
// 1) Change active texture pack
// 2) Revert to vanilla (if vanilla folder is present in the packs folder and has files)
// 3) Edit config file
// 4) Exit program

int main(int argc, char **argv) {
    // Sets working directory to application folder, used to set config filepath
    std::string directory = argv[0];
    directory.erase(directory.find_last_of('\\')+ 1);
    std::string filename = directory + "config.json";

    std::string command = "";
    std::string argument = "";

    if(argc >= 3) {
        command = argv[1];
        argument = argv[2];
    } else if(argc == 2) {
        command = argv[1];
    }

    std::vector<std::string> commandOptions = {"help", "list", "setup", "revert", "set", "config"};

    // Initialize components
    Config* configObject = new Config;
    Interface* interfaceObject = new Interface;
    Switcher* switcherObject = new Switcher;

    configObject->init(filename, directory);
    switcherObject->init(configObject);
    interfaceObject->init(configObject, switcherObject, directory);

    selectCommand(interfaceObject, command, argument);

    delete configObject;
    delete interfaceObject;
    delete switcherObject;

    return 0;
}

void selectCommand(Interface* interfaceObject, const std::string& command, const std::string& argument) {
    // if we have a command
    if(command != "") {
        
    }
}