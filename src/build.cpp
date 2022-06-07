
#include "headers/build.hpp"

Config* readConfig(string& configFile) {
    Config* newConfig = new Config();
    if (configFile == "search") {
        // we need to find a file ending in *.bob
        StringVector FWE = filesWithExt("./", fileExt);
        assert(FWE.size() > 0, "Well we don't have any files ending in *.bob, so bob cannot build this. :/");
        configFile = FWE[0]; // we can assume the first one we file is the correct one 
    }

    newConfig->fileName = configFile;
    StringVector cfData = readFile(configFile);
    for (string& line : cfData) {
        StringVector cfg = split(line, "=");
        assert(cfg.size() > 1, "Too few arguments for config > " + line);
        newConfig->config.insert(std::pair<string,string>(cfg[0], cfg[1]));
    }
    return newConfig;
}


void build(Config* conf, BuildOptions opt=BUILD_ALL) { 
    assert(inMap(conf->config, "lang"), "Language not defined.");
    printf("%s\n",conf->config["lang"].c_str());
}