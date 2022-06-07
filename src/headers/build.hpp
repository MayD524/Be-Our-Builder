#pragma once

#ifndef BUILD_HPP
#define BUILD_HPP

#include "common.hpp"


// its a bob the builder reference :)
// i had a very nice childhood B)
const string fileExt = ".bob";


enum BuildOptions {
    BUILD_ALL,
    BUILD_PARTIAL,
};


Config* readConfig(string& configFile);
void build(Config* conf, BuildOptions opt);


#endif