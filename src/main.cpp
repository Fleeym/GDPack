#include "components/config.hpp"
#include "components/interface.hpp"
#include "components/packman.hpp"
#include "components/switcher.hpp"
#include "devmode.hpp"
#include "types/colors.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

void selectCommand(Interface *interfaceObject, Config *configObject,
                   Switcher *switcherObject, const std::string &command,
                   const std::string &argument,
                   const std::vector<std::string> &commands);

// This is how I imagined the old IO system. Keeping it as a sort of time
// machine
// :)

// First, ask for the paths and Geometry Dash location if this is the first run.
// If this isn't the first run, show the options menu:
// Show how many packs are present, remember active texture pack
// 1) Change active texture pack
// 2) Revert to vanilla (if vanilla folder is present in the packs folder and
// has files) 3) Edit config file 4) Exit program

int main(int argc, char **argv) {
    fs::path directory;
#if defined(_WIN32)
    directory = std::string(std::getenv("USERPROFILE"));
#elif defined(__unix__)
    directory = std::string(std::getenv("HOME"));
#endif
    if (directory.string() == "") {
        return -1;
    }
    fs::path configFilename = directory;
    configFilename.append(".gdpack");

    if (!fs::exists(configFilename)) {
        fs::create_directory(configFilename);
    }

    configFilename.append("config.json");

    std::string command = "";
    std::string argument = "";
    std::string argument2 = "";

    if (argc == 4) {
        command = argv[1];
        argument = argv[2];
        argument2 = argv[3];
    } else if (argc == 3) {
        command = argv[1];
        argument = argv[2];
    } else if (argc == 2) {
        command = argv[1];
    }

    std::vector<std::string> commandOptions = {"help", "setup", "list",
                                               "revert", "set"};
#ifdef _DEBUG
    commandOptions.push_back("dev");
#endif

    Config *configObject = new Config;
    Interface *interfaceObject = new Interface;
    Switcher *switcherObject = new Switcher;

    std::string configString = configFilename.string();
    std::string directoryString = directory.string();

    if (!configObject->init(configString)) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Initializing Config failed.\n");
        return -1;
    }
    if (!switcherObject->init(configObject)) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Initializing Switcher failed.\n");
        return -1;
    }
    if (!interfaceObject->init(configObject, switcherObject, directoryString)) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Initializing Interface failed.\n");
        return -1;
    }
    selectCommand(interfaceObject, configObject, switcherObject, command,
                  argument, commandOptions);

    delete configObject;
    delete interfaceObject;
    delete switcherObject;
    return 0;
}

void selectCommand(Interface *interfaceObject, Config *configObject,
                   Switcher *switcherObject, const std::string &command,
                   const std::string &argument,
                   const std::vector<std::string> &commands) {
    // if the user entered a command (gdpack help)
    int commandID = -1;
    if (command != "") {
        for (int i = 0; i < commands.size(); i++) {
            if (command == commands[i] && command.size() == commands[i].size())
                commandID = i;
        }
    } else {
        commandID = 0;
    }

    if (commandID == -1) {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Invalid command, do ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack help\"");
        fmt::print(" for more info!\n");
        return;
    }

    if (argument == "help") {
        interfaceObject->showCommandHelp(command);
    } else {
        switch (commandID) {
        case 0:
            interfaceObject->showHelp(interfaceObject->getProgramVersion());
            break;
        case 1:
            configObject->setup(true);
            break;
        case 2:
            interfaceObject->listTP(argument);
            break;
        case 3:
            interfaceObject->revert(false);
            break;
        case 4:
            interfaceObject->setPack(argument);
            break;
        case 5:
            chooseCommand(argument, configObject);
            break;
        }
    }
}