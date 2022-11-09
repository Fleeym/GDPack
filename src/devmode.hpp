#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "components/config.hpp"
#include "colors.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

class Config;

using json = nlohmann::json;

void chooseCommand(const std::string &argument, Config *config);
void genCache(const std::string &gdPath);