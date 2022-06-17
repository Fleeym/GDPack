#include "switcher.hpp"

Switcher::Switcher(std::string& activePack) {
    m_activePack = activePack;
}

// Future me, I am so, so terribly sorry for this pestilence that I have inflicted upon you. I only hope you have the mercy to gaze in the mirror after rewatching this
// disaster of a function. Also sorry for playing hot potato with object references, I should have used pointers lol
void Switcher::setActivePack(std::string& packPathStr, std::string& resPathStr) {
    // names of the files we are swapping
    std::vector<std::string> resPathsPack;
    std::vector<std::string> resPathsGD;

    fs::path packPath = packPathStr;
    for(auto file : fs::directory_iterator{packPath}) {
        std::string fileStr = file.path().string();
        std::string fileName = getNameFromPath(fileStr);

        std::string vanillaStr = packPathStr;
        if(vanillaStr.at(vanillaStr.length() - 1) == '\\')
            vanillaStr.pop_back();
        vanillaStr = vanillaStr.substr(0, vanillaStr.length() - getNameFromPath(vanillaStr).length()) + "vanilla\\" + fileName;

        std::cout << vanillaStr << "\n";
        std::cout << fileStr << "\n";
        fs::path resPath = resPathStr + fileName;
    }
}
std::string Switcher::getNameFromPath(std::string& path) {
    std::string temp = path;
    if(temp.at(temp.length() - 1) == '\\')
        temp.pop_back();
    return temp.substr(temp.find_last_of('\\') + 1, (temp.length() - temp.find_last_of('\\')));
}

void Switcher::setDefaultActivePack(std::string& name) {
    m_activePack = name;
}

void createVanillaFolder() {

}

