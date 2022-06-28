#include "interface.hpp"

bool Interface::init(Config* configObject, Switcher* switcherObject, std::string& directory) {
    m_directory = directory;
    m_config = configObject;
    m_switcher = switcherObject;

    m_packNames = configObject->getPackNames();
    m_packPaths = configObject->getPackPaths();
    m_packs = configObject->getPacks();
    return true;
}

void Interface::listTP(const std::string& argument) {
    if(argument == "") {
        fmt::print(fg(fmt::color::yellow), "GDPack CLI ");
        fmt::print(fg(fmt::color::purple), "v{}\n", m_programVersion);
    
        if(m_packNames.size() == 0) {
            fmt::print(fg(fmt::color::orange), "You don't have any packs installed!\n");
            return;
        }
        fmt::print(fg(fmt::color::orange), "Here's a list of all of your texture packs: \n\n");
    
        int i = 1;
        for(auto pack : m_packNames) {
            if(m_config->getActivePack()->getJson()["name"] == pack) {
                fmt::print(fg(fmt::color::cyan), "[{}] ", i);
                fmt::print("{} ", pack);
                fmt::print(fg(fmt::color::green), "[Active]\n");
            } else {
                fmt::print(fg(fmt::color::cyan), "[{}] ", i);
                fmt::print("{}\n", pack);
            }
            ++i;
        }
    } else {
        bool containsDigits = (argument.find_first_not_of("0123456789") == std::string::npos);
        if(!containsDigits) {
            fmt::print(fg(fmt::color::red), "[ERROR]: ");
            fmt::print("Invalid argument, try ");
            fmt::print(fg(fmt::color::yellow), "\"gdpack list help\"");
            return;
        }
        int index = std::stoi(argument);
        if(index > m_packNames.size() || index < 1) {
            fmt::print(fg(fmt::color::red), "[ERROR]: ");
            fmt::print("Invalid index, use ");
            fmt::print(fg(fmt::color::yellow), "\"gdpack list\"");
            fmt::print(" to see available packs.\n");
            return;
        }
        fmt::print("Showing info for pack: ");
        fmt::print(fg(fmt::color::yellow), "{}\n\n", m_packNames.at(index - 1));
        json manifest = m_packs.at(index - 1)->getJson();

        fmt::print(fg(fmt::color::green_yellow), "Author: ");
        fmt::print("{}\n", manifest["author"]);

        fmt::print(fg(fmt::color::green_yellow), "Pack Version: ");
        fmt::print("{}\n", manifest["version"]);

        fmt::print(fg(fmt::color::green_yellow), "Description: ");
        fmt::print("{}\n", manifest["description"]);

        fmt::print(fg(fmt::color::green_yellow), "GD Version: ");
        fmt::print("{}\n", manifest["gdVersion"]);

        fmt::print(fg(fmt::color::green_yellow), "Pack Path: ");
        fmt::print("{}\n", manifest["path"]);
    }
}

void Interface::setPack(const std::string& indexStr) {
    bool containsDigits = (indexStr.find_first_not_of("0123456789") == std::string::npos);
    if(indexStr == "" || !containsDigits) {
        fmt::print(fg(fmt::color::red), "[ERROR]: ");
        fmt::print("Invalid argument. Argument should be the pack index. Use ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack list\"");
        fmt::print(" to see available packs.\n");
        return;
    }
    int index = std::stoi(indexStr);
    if(m_packNames.at(index - 1) == "vanilla") {
        fmt::print(fg(fmt::color::red), "[ERROR]: ");
        fmt::print("Can't switch to vanilla using this command, instead use ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack revert\"\n");
        return;
    }
    if(index <= m_packPaths.size() && index > 0) {
        if(m_config->getActivePack()->getJson()["name"] != "vanilla")
            revert(true);
        m_switcher->setActivePack(m_packs.at(index - 1), false);
    } else {
        fmt::print(fg(fmt::color::red), "[ERROR]: ");
        fmt::print("Invalid index. Use ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack list\"");
        fmt::print(" to see available packs.\n");
    }
}

void Interface::revert(bool fromCommand) {
    if(m_config->getActivePack()->getJson()["name"] == "vanilla") {
        if(!fromCommand) {
            fmt::print(fg(fmt::color::red), "[ERROR]: ");
            fmt::print(fg(fmt::color::yellow), "\"vanilla\"");
            fmt::print(" is already the default pack.\n");
            return;
        }
    }
    int64_t position = 0;
    auto found = std::find(m_packNames.begin(), m_packNames.end(), "vanilla");
    if(found != std::end(m_packNames)) {
        position = std::distance(m_packNames.begin(), found);
        // std::cout << "Pack position: " << position << '\n';
    }
    m_switcher->setActivePack(m_packs.at(position), fromCommand);
}

void Interface::showHelp(std::string& version) {
    fmt::print(fg(fmt::color::yellow), "GDPack ");
    fmt::print(fg(fmt::color::purple), "v{}", version);
    fmt::print(" [COMMAND] [ARGUMENT]\n"
                "The CLI Geometry Dash texture pack manager!\n\n");
    fmt::print(fg(fmt::color::orange), "Here is a list of possible commands: \n");

    fmt::print(fg(fmt::color::cyan), "* help -> ");
    fmt::print("Shows this dialogue. Can be used as argument for other commands.\n");

    fmt::print(fg(fmt::color::cyan), "* setup -> ");
    fmt::print("Repeats the first-run setup.\n");

    fmt::print(fg(fmt::color::cyan), "* list -> ");
    fmt::print("Lists all installed packs.\n");

    fmt::print(fg(fmt::color::cyan), "* revert -> ");
    fmt::print("Reverts the game to vanilla resources.\n");

    fmt::print(fg(fmt::color::cyan), "* set [INDEX] -> ");
    fmt::print("Sets the active pack.\n");
}

void Interface::showCommandHelp(const std::string& command) {
    fmt::print(fg(fmt::color::yellow), "GDPack ");
    fmt::print(fg(fmt::color::purple), "v{}", m_programVersion);
    fmt::print(" [COMMAND] [ARGUMENT]\n"
                "The CLI Geometry Dash texture pack manager!\n\n");
    if(command == "setup") {
        fmt::print(fg(fmt::color::yellow), "Command \"setup\": ");
        fmt::print("Repeats the first-run setup, used to set the Geometry Dash path if needed.\nThis command doesn't take any arguments.\n");
    } else if(command == "list") {
        fmt::print(fg(fmt::color::yellow), "Command \"list\" [INDEX]: ");
        fmt::print("Lists the packs present in the root directory of GDPack. Used along with ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack set [INDEX]\"");
        fmt::print(" to switch packs.\n");
        fmt::print("If you enter an index, you will get information about the selected pack.\n");
    } else if(command == "revert") {
        fmt::print(fg(fmt::color::yellow), "Command \"revert\": ");
        fmt::print("Reverts to the vanilla textures. Basically runs ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack set [vanilla-index]\". ");
        fmt::print(fg(fmt::color::orange), "DO NOT use this while the game is running.\n");
        fmt::print(fg(fmt::color::lavender), "[IMPORTANT]: The \"vanilla\" pack is the state of your Resources folder when GDPack first ran. That means that revert won't revert to vanilla textures, but it will revert to that state.\n");
    } else if(command == "set") {
        fmt::print(fg(fmt::color::yellow), "Command \"set\" [INDEX]: ");
        fmt::print("Sets the active pack to the index specified. ");
        fmt::print(fg(fmt::color::orange), "DO NOT use this while the game is running. ");
        fmt::print("The index can be found by using ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack list\".\n");
    }
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

std::vector<PackManager*> Interface::getPacks() {
    return m_packs;
}

Interface::~Interface() {
    for(auto pack : m_packs) {
        delete pack;
    }
}