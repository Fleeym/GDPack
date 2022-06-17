#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class Config {
private:
    json m_json;
    std::string m_filename;
    std::string m_packsLocation;

public:
    // Checks if the config file exists
    bool fileExists();
    // Reads the config file and turns it into a json object
    bool read();
    // Writes the json object to the config file
    void write();
    // Constructor, gets the filename of the config file
    Config(std::string& filename);
    void print(); // testing
    void setPacksLocation(std::string& path);
};