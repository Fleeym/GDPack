#include "interface.hpp"

bool Interface::init(Config *configObject, Switcher *switcherObject, std::string &directory)
{
    m_directory = directory;
    m_config = configObject;
    m_switcher = switcherObject;

    m_packNames = configObject->getPackNames();
    m_packPaths = configObject->getPackPaths();
    m_packs = configObject->getPacks();
    return true;
}

void Interface::listTP(const std::string &argument)
{
    if (argument == "")
    {
        fmt::print(fg(TITLE_COLOR), "GDPack ");
        fmt::print(fg(VERSION_COLOR), "v{}\n", m_programVersion);

        if (m_packNames.size() == 0)
        {
            fmt::print(fg(INFO_COLOR), "You don't have any packs installed!\n");
            return;
        }
        fmt::print(fg(INFO_COLOR), "Here's a list of all of your texture packs: \n\n");

        int i = 1;
        for (auto pack : m_packNames)
        {
            json activePackJson = m_config->getActivePack()->getJson();
            if (activePackJson["name"] == pack)
            {
                fmt::print(fg(INDEX_COLOR), "[{}] ", i);
                fmt::print("{} ", pack);
                fmt::print(fg(ACTIVE_COLOR), "[Active]\n");
            }
            else
            {
                fmt::print(fg(INDEX_COLOR), "[{}] ", i);
                fmt::print("{}\n", pack);
            }
            ++i;
        }
    }
    else
    {
        bool containsDigits = (argument.find_first_not_of("0123456789") == std::string::npos);
        if (!containsDigits)
        {
            fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print("Invalid argument, try ");
            fmt::print(fg(TITLE_COLOR), "\"gdpack list help\"");
            return;
        }
        int index = std::stoi(argument);
        if (index > m_packNames.size() || index < 1)
        {
            fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print("Invalid index, use ");
            fmt::print(fg(TITLE_COLOR), "\"gdpack list\"");
            fmt::print(" to see available packs.\n");
            return;
        }
        fmt::print("Showing info for pack: ");
        fmt::print(fg(TITLE_COLOR), "{}\n\n", m_packNames.at(index - 1));
        json manifest = m_packs.at(index - 1)->getJson();

        fmt::print(fg(PROP_COLOR), "Author: ");
        fmt::print("{}\n", manifest["author"]);

        fmt::print(fg(PROP_COLOR), "Pack Version: ");
        fmt::print("{}\n", manifest["version"]);

        fmt::print(fg(PROP_COLOR), "Description: ");
        fmt::print("{}\n", manifest["description"]);

        fmt::print(fg(PROP_COLOR), "GD Version: ");
        fmt::print("{}\n", manifest["gdVersion"]);

        fmt::print(fg(PROP_COLOR), "Pack Path: ");
        fmt::print("{}\n", manifest["path"]);
    }
}

void Interface::setPack(const std::string &indexStr)
{
    bool containsDigits = (indexStr.find_first_not_of("0123456789") == std::string::npos);
    if (indexStr == "" || !containsDigits)
    {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Invalid argument. Argument should be the pack index. Use ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack list\"");
        fmt::print(" to see available packs.\n");
        return;
    }
    int index = std::stoi(indexStr);
    if (m_packNames.at(index - 1) == "vanilla")
    {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Can't switch to vanilla using this command, instead use ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack revert\"\n");
        return;
    }
    if (index <= m_packPaths.size() && index > 0)
    {
        if (m_config->getActivePack()->getJson()["name"] != "vanilla")
            revert(true);
        m_switcher->setActivePack(m_packs.at(index - 1), false);
    }
    else
    {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Invalid index. Use ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack list\"");
        fmt::print(" to see available packs.\n");
    }
}

void Interface::revert(bool fromCommand)
{
    if (m_config->getActivePack()->getJson()["name"] == "vanilla")
    {
        if (!fromCommand)
        {
            fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
            fmt::print(fg(TITLE_COLOR), "\"vanilla\"");
            fmt::print(" is already the default pack.\n");
            return;
        }
    }
    int64_t position = 0;
    auto found = std::find(m_packNames.begin(), m_packNames.end(), "vanilla");
    if (found != std::end(m_packNames))
    {
        position = std::distance(m_packNames.begin(), found);
        // std::cout << "Pack position: " << position << '\n';
    }
    m_switcher->setActivePack(m_packs.at(position), fromCommand);
}

void Interface::showHelp(std::string &version)
{
    fmt::print(fg(TITLE_COLOR), "GDPack ");
    fmt::print(fg(VERSION_COLOR), "v{}", version);
    fmt::print(" [COMMAND] [ARGUMENT]\n"
               "The CLI Geometry Dash texture pack manager!\n\n");
    fmt::print(fg(INFO_COLOR), "Here is a list of possible commands: \n");

    fmt::print(fg(TITLE_COLOR), "* help -> ");
    fmt::print("Shows this dialogue. Can be used as argument for other commands.\n");

    fmt::print(fg(TITLE_COLOR), "* setup -> ");
    fmt::print("Repeats the first-run setup.\n");

    fmt::print(fg(TITLE_COLOR), "* list [INDEX] -> ");
    fmt::print("Lists all installed packs.\n");

    fmt::print(fg(TITLE_COLOR), "* revert -> ");
    fmt::print("Reverts the game to vanilla resources.\n");

    fmt::print(fg(TITLE_COLOR), "* set [INDEX] -> ");
    fmt::print("Sets the active pack.\n");
}

void Interface::showCommandHelp(const std::string &command)
{
    fmt::print(fg(TITLE_COLOR), "GDPack ");
    fmt::print(fg(fmt::color::medium_purple), "v{}", m_programVersion);
    fmt::print(" [COMMAND] [ARGUMENT]\n"
               "The CLI Geometry Dash texture pack manager!\n\n");
    if (command == "setup")
    {
        fmt::print(fg(TITLE_COLOR), "Command \"setup\": ");
        fmt::print("Repeats the first-run setup, used to set the Geometry Dash path if needed.\nThis command doesn't take any arguments.\n");
    }
    else if (command == "list")
    {
        fmt::print(fg(TITLE_COLOR), "Command \"list\" [INDEX]: ");
        fmt::print("Lists the packs present in the root directory of GDPack. Used along with ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack set [INDEX]\"");
        fmt::print(" to switch packs.\n");
        fmt::print("If you enter an index, you will get information about the selected pack.\n");
    }
    else if (command == "revert")
    {
        fmt::print(fg(TITLE_COLOR), "Command \"revert\": ");
        fmt::print("Reverts to the vanilla textures. Basically runs ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack set [vanilla-index]\". ");
        fmt::print(fg(INFO_COLOR), "DO NOT use this while the game is running.\n");
        fmt::print(fg(INFO_COLOR), "[IMPORTANT]: ");
        fmt::print("The ");
        fmt::print(fg(TITLE_COLOR), "\"vanilla\"");
        fmt::print(" pack is the state of your Resources folder when GDPack first ran. That means that revert won't revert to vanilla textures, but it will revert to that state.\n");
    }
    else if (command == "set")
    {
        fmt::print(fg(TITLE_COLOR), "Command \"set\" [INDEX]: ");
        fmt::print("Sets the active pack to the index specified. ");
        fmt::print(fg(INFO_COLOR), "DO NOT use this while the game is running. ");
        fmt::print("The index can be found by using ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack list\".\n");
    }
    else if (command == "dev")
    {
        fmt::print("This is the help message, helpful right?\n");
    }
}

std::string &Interface::getProgramVersion()
{
    return m_programVersion;
}

void Interface::setPackPaths(const std::vector<std::string> packPaths)
{
    m_packPaths = packPaths;
}

void Interface::setPackNames(const std::vector<std::string> packNames)
{
    m_packNames = packNames;
}

std::vector<PackManager *> Interface::getPacks()
{
    return m_packs;
}

Interface::~Interface()
{
    for (auto pack : m_packs)
    {
        delete pack;
    }
}