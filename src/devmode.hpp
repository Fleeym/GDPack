#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "components/config.hpp"
#include "types/colors.hpp"

namespace fs = std::filesystem;

class Config;

using json = nlohmann::json;

void chooseCommand(const std::string &argument, Config *config);
void gencache(const std::string &gdPath);
std::string getNameFromPath(const std::string &path);