#include "switcher.hpp"


void Switcher::init(Config *config) {
    m_config = config;
}

// Future me, I am so, so terribly sorry for this pestilence that I have inflicted upon you. I only hope you have the mercy to gaze in the mirror after rewatching this
// disaster of a function. Also sorry for playing hot potato with object references, I should have used pointers lol
void Switcher::setActivePack(const std::string& packPathString, const std::string& gdResPathString, std::string& packName) {
    //std::cout << packPathString << "\n" << gdResPathString << "\n";
    std::string packPathFilesString = packPathString + "\\Resources";
    std::string gdResPathFilesString = gdResPathString + "\\Resources";

    // Paths to <pack>/Resources, and GD/Resources respectively
    fs::path gdResPathFiles = gdResPathFilesString;
    fs::path packPathFiles = packPathFilesString;

    // Paths to root folder of pack and GD folder
    fs::path packPath = packPathString;
    fs::path gdResPath = gdResPathString;

    std::vector<std::string> filesToCopy;
    if(packName == m_config->getActivePack()) {
        fmt::print(fg(fmt::color::red), "This pack is already in use.\n");
        return;
    }
    const auto copyOptions = fs::copy_options::overwrite_existing
                            | fs::copy_options::recursive;
    
    // Iterate in the texture pack folder and remember which files to move
    auto iterator = fs::directory_iterator(packPathFiles);
    for(auto file : iterator) {
        std::string tempStr = file.path().string();
        std::string fileName = getNameFromPath(tempStr);
        filesToCopy.push_back(fileName);
    }

    std::string vanillaPathStr;

    if(m_config->getActivePack() == "vanilla") {
        vanillaPathStr = createVanilla().string();
        if(vanillaPathStr.at(vanillaPathStr.length() - 1) == '\\') 
            vanillaPathStr.pop_back();
    }

    
    iterator = fs::directory_iterator(gdResPathFiles);
    for(auto file : iterator) {  
        std::string fileName = getNameFromPath(file.path().string());
        auto neededFile = std::find(filesToCopy.begin(), filesToCopy.end(), fileName);
        if(neededFile != std::end(filesToCopy)) {
            // Move original files to vanilla pack
            if(m_config->getActivePack() == "vanilla") {
                std::string destinationString = vanillaPathStr + "\\" + fileName;
                fs::path destination = destinationString;
                if(!fs::exists(destination))
                    fs::copy(file.path(), destination);
            }
        }
    }
    fs::copy(packPathFiles, gdResPathFiles, copyOptions);
    m_config->setActivePack(packName);
}
std::string Switcher::getNameFromPath(std::string& path) {
    std::string temp = path;
    if(temp.at(temp.length() - 1) == '\\')
        temp.pop_back();
    return temp.substr(temp.find_last_of('\\') + 1, (temp.length() - temp.find_last_of('\\')));
}

fs::path Switcher::createVanilla() {
    // Creates vanilla folder if it doesn't exist
    std::string vanillaStr = m_config->getPacksPath();
    vanillaStr += "\\vanilla";
    if(vanillaStr.at(vanillaStr.length() - 1) == '\\')
        vanillaStr.pop_back();

    fs::path vanillaPath = vanillaStr;
    if(!fs::exists(vanillaPath)) {
        fs::create_directory(vanillaPath);
    }
    vanillaPath.append("Resources");
    if(!fs::exists(vanillaPath)) {
        fs::create_directory(vanillaPath);
    }   
    return vanillaPath;
}   

