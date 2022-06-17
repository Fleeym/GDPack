#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include <string>

using json = nlohmann::json;
namespace fs = std::filesystem;

class Config {
private:
    std::string m_configLiteral;
    json m_json;
    std::string m_filename;
    std::string m_packsLocation;

public:
    // Checks if the config file exists
    bool exists();
    // Reads the config file and turns it into a json object
    void readJson();
    // Writes the json object to the config file
    void writeJson();
    // Constructor, gets the filename of the config file
    Config(char* filename);
};