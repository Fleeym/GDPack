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

    if(!m_config->fileExists()) {
        m_config->setup(false);
    }

    m_packPaths = getPackPaths();
    m_packNames = getPackNames(m_packPaths);
}

std::vector<std::string> Interface::getPackPaths(){
    fs::path packsPath = m_directory;
    std::vector<std::string> packPaths;

    for(auto entry : fs::directory_iterator{packsPath}) {
        if(fs::is_directory(entry)) {
            // Make one array of paths of the packs, and one with just their names

            std::string entryString = entry.path().string();
            packPaths.push_back(entryString);
        }
    }
    return packPaths;
}

std::vector<std::string> Interface::getPackNames(const std::vector<std::string>& packPaths) {
    std::vector<std::string> packNames;
    for(auto path : packPaths) {
        if(packPaths[packPaths.size() - 1] == "\\") {
            packNames.pop_back();
        }
        std::string temp = path;
        temp = path.substr(path.find_last_of('\\') + 1, (path.length() - path.find_last_of('\\')));
        packNames.push_back(temp);
    }
    return packNames;
}

void Interface::listTP() {
    fmt::print(fg(fmt::color::yellow), "GDPack CLI ");
    fmt::print(fg(fmt::color::purple), "v{}\n", m_programVersion);
    fmt::print(fg(fmt::color::orange), "Here's a list of all of your texture packs: \n\n");
    
    int i = 1;
    for(auto pack : m_packNames) {
        if(m_config->getActivePack() == pack) {
            std::cout << i << ") " << pack << "[*]" << '\n';
        } else {
            std::cout << i << ") " << pack << "\n";
        }
        ++i;
    }
}

void Interface::setPack(const std::string& indexStr) {
    bool containsDigits = (indexStr.find_first_not_of("0123456789") == std::string::npos);
    if(indexStr == "" || !containsDigits) {
        fmt::print(fg(fmt::color::red), "Invalid argument. Argument should be the pack index. Use \"gdpack list\" to see available packs.");
        return;
    }
    int index = std::stoi(indexStr);
    if(index <= m_packPaths.size() && index > 0) {
        m_switcher->setActivePack(m_packPaths.at(index - 1), m_config->getGeometryDashPath(), m_packNames.at(index - 1));
    } else {
        fmt::print(fg(fmt::color::red), "Invalid index. Use \"gdpack list\" to see available packs.");
    }
}

void Interface::revert() {
    if(m_config->getActivePack() == "vanilla") {
        fmt::print(fg(fmt::color::red), "\"vanilla\" is already the default pack.\n");
        return;
    }

    int64_t position = 0;
    auto found = std::find(m_packNames.begin(), m_packNames.end(), "vanilla");
    if(found != std::end(m_packNames)) {
        position = std::distance(m_packNames.begin(), found);
        // std::cout << "Pack position: " << position << '\n';
    }
    m_switcher->setActivePack(m_packPaths.at(position), m_config->getGeometryDashPath(), m_packNames.at(position));
}

void Interface::showHelp(std::string& version) {
    fmt::print(fg(fmt::color::yellow), "GDPack ");
    fmt::print(fg(fmt::color::purple), "v{}", version);
    fmt::print(" [COMMAND] [ARGUMENT]\n"
                "The CLI Geometry Dash texture pack manager!\n\n");
    fmt::print(fg(fmt::color::orange), "Here is a list of possible commands: \n");
    fmt::print(fg(fmt::color::cyan),
        " * help -> Shows this dialogue. Can be used as argument for other commands.\n"
        " * setup -> Repeats the first-run setup.\n"
        " * list -> Lists all installed packs.\n"
        " * revert -> Reverts the game to vanilla resources.\n"
        " * set [INDEX] -> Sets the active pack.\n"
    );
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
        fmt::print(fg(fmt::color::yellow), "Command \"list\": ");
        fmt::print("Lists the packs present in the root directory of GDPack. Used along with ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack set [INDEX]\"");
        fmt::print(" to switch packs.\n");
    } else if(command == "revert") {
        fmt::print(fg(fmt::color::yellow), "Command \"revert\": ");
        fmt::print("Reverts to the vanilla textures. Basically runs ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack set [vanilla-index]\".\n");
        fmt::print(fg(fmt::color::orange), "[IMPORTANT]: The \"vanilla\" pack is the state of your Resources folder when GDPack first ran. That means that revert won't revert to vanilla textures, but it will revert to that state.\n");
    } else if(command == "set") {
        fmt::print(fg(fmt::color::yellow), "Command \"set\" [INDEX]: ");
        fmt::print("Sets the active pack to the index specified. The index can be found by using ");
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