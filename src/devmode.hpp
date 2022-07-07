#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "config.hpp"

class Config; // why the fuck, what the fuck, for what god forsaken reason do i need to write this

namespace fs = std::filesystem;

using json = nlohmann::json;

void chooseCommand(const std::string& argument, Config* config);
void gencache(const std::string& gdPath);
std::string getNameFromPath(const std::string& path);