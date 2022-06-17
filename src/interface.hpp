#pragma once

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Interface {
private:

public:
    void init(Config& config);
    void setup(Config& config);
    void mainMenu();
    void changeTP();
    void revert();
    void editConfig();
};