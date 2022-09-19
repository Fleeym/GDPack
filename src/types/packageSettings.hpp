#pragma once

#include <string>

struct PackageSettings {
    std::string name;
    std::string path;
    std::string author;
    std::string description;
    std::string version;
    std::string gdVersion = "2.1";
};