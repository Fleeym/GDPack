#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;

using json = nlohmann::json;

void chooseCommand(const std::string& argument, Config* config);
void gencache(const std::string& gdPath);
std::string getNameFromPath(const std::string& path);