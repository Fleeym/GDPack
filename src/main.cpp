#include "config.hpp"
#include "interface.hpp"
#include "switcher.hpp"

#include <vector>
#include <algorithm>
#include <iterator>

int getCommand(std::string&, std::vector<std::string>&);
void selectCommand(Interface* interfaceObject, Config* configObject, Switcher* switcherObject, 
                    const std::string& command, const std::string& argument, const std::vector<std::string>& commands);

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
    std::string argument2 = "";

    if(argc == 4) {
        command = argv[1];
        argument = argv[2];
        argument2 = argv[3];
    } else if(argc == 3) {
        command = argv[1];
        argument = argv[2];
    } else if(argc == 2) {
        command = argv[1];
    }

    const std::vector<std::string> commandOptions = {"help", "setup", "list", "revert", "set", "config"};

    // Initialize components
    Config* configObject = new Config;
    Interface* interfaceObject = new Interface;
    Switcher* switcherObject = new Switcher;

    configObject->init(filename, directory);
    switcherObject->init(configObject);
    interfaceObject->init(configObject, switcherObject, directory);

    selectCommand(interfaceObject, configObject, switcherObject,  command, argument, commandOptions);

    delete configObject;
    delete interfaceObject;
    delete switcherObject;

    return 0;
}

void selectCommand(Interface* interfaceObject, Config* configObject, Switcher* switcherObject,
                  const std::string& command, const std::string& argument, const std::vector<std::string>& commands) {
    // if the user entered a command (gdpack help)
    int commandID = -1;
    if(command != "") {
        for(int i = 0; i < commands.size() - 1; i++) {
            if(command == commands[i] && command.size() == commands[i].size())
                commandID = i;
        }
    } else {
        commandID = 0;
    }

    if(commandID == -1) {
        fmt::print(fg(fmt::color::red), "Invalid command, do \"gdpack help\" for more info!");
        return;
    }

    switch(commandID) {
        case 0: interfaceObject->showHelp(interfaceObject->getProgramVersion()); break;
        case 1: configObject->setup(true); break;
        case 2: interfaceObject->listTP(); break;
        case 3: interfaceObject->revert(); break;
    }

    if(argument != "") {
        switch(commandID) {
            case 4: interfaceObject->setPack(argument);
            case 5: interfaceObject->editConfig();
        }
    }
}