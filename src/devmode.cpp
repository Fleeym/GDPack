#include "devmode.hpp"
#include "config.hpp"

void chooseCommand(const std::string& argument, Config* config) {
    if(argument == "cgen") {
        gencache(config->getGeometryDashPath());
    } else {
        fmt::print(fg(fmt::color::red), "[ERROR]: ");
        fmt::print("Invalid argument, use ");
        fmt::print(fg(fmt::color::yellow), "\"gdpack dev help\" ");
        fmt::print("to see valid arguments.\n");
    }
}

void gencache(const std::string& gdPath) {
    std::ofstream out("cache.json");
    json jsonFile;

    std::vector<uintmax_t> fileSizes;
    fs::path path = gdPath;
    path.append("Resources");
    auto iterator = fs::directory_iterator(path);

    for(auto file : iterator) {
        std::string fileName = getNameFromPath(file.path().string());
        uintmax_t fileSize = fs::file_size(file.path());
        jsonFile[fileName] = fileSize;

        fmt::print(fg(fmt::color::light_green), "[DEBUG]: ");
        fmt::print("File {}, size {}\n", fileName, fileSize);
    }
    out << jsonFile;

    out.close();
}

std::string getNameFromPath(const std::string& path) {
    std::string temp = path;
    if(temp.at(temp.length() - 1) == '\\')
        temp.pop_back();
    return temp.substr(temp.find_last_of('\\') + 1, (temp.length() - temp.find_last_of('\\')));
}