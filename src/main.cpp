#include <iostream>
#include <string>
#include <vector>

#include "headers/defines.hpp"
#include "headers/build.hpp"

using std::string;
using std::vector;

string defaultConfig = "search";

StringVector argvToVector(int argc, char *argv[]) {
    StringVector result;
    for (int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
}

int main (int argc, char* argv[]) {
    StringVector args = argvToVector(argc, argv);
    
    Config* cf = readConfig(defaultConfig);

    build(cf, BUILD_ALL);

    return 0;
}