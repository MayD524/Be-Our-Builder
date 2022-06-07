#pragma once

#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#ifdef _WIN32
    #include <windows.h>
    #include <tchar.h>
    #include <strsafe.h>

    #define TOCHAR_MAX MAX_PATH

    TCHAR* strToTCHAR(std::string ins);
    std::string WCHARToStr(WCHAR* wStr);

#else
    #include <dirent.h>
#endif


#include "defines.hpp"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::getline;

// exception classes for helpers
class assert_exception : public std::exception {
public:
    assert_exception(const std::string& message) : message(message) {}
    const char* what() const throw() {
        return message.c_str();
    }
private:
    std::string message;
};

// string util
bool inString(const string& str, const string& lookFor);
StringVector split(string str, const string& delim);

// direct file IO
StringVector readFile(const string& fileName);
void writeFile(const string& fileName, const StringVector& lines);

// helpers
void assert(bool condition, const string& message);
bool inMap(StringMap mp, string lookFor);

// File system wizardry 
void copyFile(const string& source, const string& destination);
void copyFolder(const string& source, const string& destination);
void removeFile(const string& fileName);
void removeFolder(const string& folderName);
bool fileExists(const string& fileName);
StringVector listFiles(const string& pwd, bool recursive);
StringVector filesWithExt(const string& pwd, const string& ext);

// general data structures
struct Config {
    string fileName;
    StringMap config;
};

#endif // COMMON_HPP