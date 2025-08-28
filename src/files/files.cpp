#include "files.h"
#include <sstream>

std::string FileToString(const std::ifstream &file) {
    std::stringstream buffer;

    buffer << file.rdbuf();

    std::string str = buffer.str();

    return str;
}
