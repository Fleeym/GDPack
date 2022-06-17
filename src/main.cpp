#include "config.hpp"
#include "interface.hpp"

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
    

    // Initialize components
    Config configObject(filename);
    Interface interfaceObject;
    interfaceObject.init(configObject, directory);
    return 0;
}