#include "devmode.hpp"

void chooseCommand(const std::string &argument, Config *config) {
    if (argument == "cgen") {
        gencache(config->getGeometryDashPath());
    } else {
        fmt::print(fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print("Invalid argument, use ");
        fmt::print(fg(TITLE_COLOR), "\"gdpack dev help\" ");
        fmt::print("to see valid arguments.\n");
    }
}

void gencache(const std::string &gdPath) {
    const std::string fileName = "cache.json";

    std::ofstream out(fileName);
    if (!out) {
        fmt::print(stderr, fg(ERROR_COLOR), "[ERROR]: ");
        fmt::print(stderr, "Error writing to file {}\n", fileName);
    }
    json jsonFile;

    std::vector<uintmax_t> fileSizes;
    fs::path path = gdPath;
    path.append("Resources");
    auto iterator = fs::directory_iterator(path);

    for (auto file : iterator) {
        std::string fileName = getNameFromPath(file.path().string());
        uintmax_t fileSize = fs::file_size(file.path());
        jsonFile[fileName] = fileSize;
#ifdef _DEBUG
        fmt::print(fg(DEBUG_COLOR), "[DEBUG]: ");
        fmt::print("File {}, size {}\n", fileName, fileSize);
#endif
    }
    out << jsonFile;
    out.close();
    fmt::print(fg(SUCCESS_COLOR), "[SUCCESS]: ");
    fmt::print("Exported vanilla file sizes to {}!\n", fileName);
}

std::string getNameFromPath(const std::string &path) {
    std::string temp = path;
    char separator = '/';
#if defined(_WIN32)
    separator = '\\'
#endif
                if (temp.at(temp.length() - 1) == separator) temp.pop_back();
    return temp.substr(temp.find_last_of(separator) + 1,
                       (temp.length() - temp.find_last_of(separator)));
}