#include "utils.hpp"

std::string getNameFromPath(const std::string &path) {
    std::string temp = path;
    char separator = '/';
    
#if defined(_WIN32)
    separator = '\\';
#endif
    if (temp.at(temp.length() - 1) == separator) temp.pop_back();

    return temp.substr(temp.find_last_of(separator) + 1, (temp.length() - temp.find_last_of(separator)));
}

bool isDebug() {
#ifndef _optimize_
    return true;
#endif
    return false;
}