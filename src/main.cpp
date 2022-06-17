#include "config.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// First, ask for the paths location if this is the first run.
// If this isn't the first run, show the options menu:
// Show how many packs are present, remember active texture pack
// 1) Change active texture pack
// 2) Revert to vanilla (if vanilla folder is present in the packs folder and has files)
// 3) Exit program

int main() {
    std::string filename = "config.json";
    std::string packsPath = "D:\\Packs";
    Config config(filename);
    config.setPacksLocation(packsPath);
    config.print();
    return 0;
}