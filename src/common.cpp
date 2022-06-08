
#include "headers/common.hpp"

#ifdef _WIN32
    TCHAR* strToTCHAR(string ins) {
        
        TCHAR* out = new TCHAR[ins.size() + 1];
        
        out[ins.size()] = 0;
        std::copy(ins.begin(), ins.end(), out);

        return out;
    }

    string WCHARToStr(WCHAR* wStr) {
        char ch[260];
        char DefChar = ' ';

        WideCharToMultiByte(CP_ACP, 0, wStr, -1, ch, 260, &DefChar, NULL);
        string out(ch);
        return out;
    }

#endif


StringVector readFile(const string& fileName) {
    StringVector result;
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            result.push_back(line);
        }
        file.close();
    }
    return result;
}

void writeFile(const string& fileName, const StringVector& lines) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (StringVector::const_iterator it = lines.begin(); it != lines.end(); it++) {
            file << *it << "\n";
        }
        file.close();
    }
}

void assert(bool condition, const string& message) {
    #ifdef ENABLE_ASSERT
        if (!condition) {
            throw assert_exception(message);
        }
    #else
        if (!condition) {
            std::cout << "Assertion failed: " << message << std::endl;
        }
    #endif
}

bool inMap(StringMap mp, string lookFor) {
    return mp.find(lookFor) != mp.end();
}

void copyFile(const string& source, const string& destination) {
    ifstream sourceFile(source);
    ofstream destinationFile(destination);
    if (sourceFile.is_open() && destinationFile.is_open()) {
        string line;
        while (getline(sourceFile, line)) {
            destinationFile << line << "\n";
        }
        sourceFile.close();
        destinationFile.close();
    }
}

void copyFolder(const string& source, const string& destination) {
    StringVector files = readFile(source);
    for (StringVector::const_iterator it = files.begin(); it != files.end(); it++) {
        copyFile(source + "/" + *it, destination + "/" + *it);
    }
}

void removeFile(const string& fileName) {
    remove(fileName.c_str());
}

void removeFolder(const string& folderName) {
    StringVector files = readFile(folderName);
    for (StringVector::const_iterator it = files.begin(); it != files.end(); it++) {
        removeFile(folderName + "/" + *it);
    }
    remove(folderName.c_str());
}

bool fileExists(const string& fileName) {
    ifstream file(fileName);
    bool isOpen = file.is_open();
    file.close();
    return isOpen;
}

bool inString(const string& str, const string& subStr) {
    return str.find(subStr) != string::npos;
}

StringVector split(string str, const string& delim, int splitCount=-1) {
    StringVector out;

    string token;
    size_t pos = 0;
    int splitCnt = 0;
    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos);
        out.push_back(token);
        str.erase(0, pos+delim.length());
        splitCnt++;
        if (splitCnt == splitCount) { break; }
    }
    out.push_back(str);
    return out;
}

bool createFolder(const string& path) {
    if (CreateDirectory((LPCSTR)path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
        return true;
    }
    return false;
}

bool stringEnd(const string& str, const string& suff) {
    if (str.length() < suff.length()) return false;
    return (0 == str.compare(str.length() - suff.length(), suff.length(), suff));
}

StringVector listFiles(const string& pwd, bool recursive=true) {
    StringVector lsFiles;
    if (stringEnd(pwd, "..")) {
        return lsFiles;
    }
    #ifdef _WIN32
        WIN32_FIND_DATA fd;
        TCHAR szDir[MAX_PATH];
        size_t lengthOfArg;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        DWORD dwError = 0;
        TCHAR* tPWD = strToTCHAR(pwd);
        StringCchLength(tPWD, MAX_PATH, &lengthOfArg);
        assert(lengthOfArg < (MAX_PATH - 3), "Directory path is too long.\n");

        StringCchCopy(szDir, MAX_PATH, tPWD);
        StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

        hFind = FindFirstFile(szDir, &fd);
        assert(INVALID_HANDLE_VALUE != hFind, "FindFirstFile has failed, Invalid handle");
        while (FindNextFile(hFind, &fd) != 0) {
            if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
            {
                string path = pwd + (char*) fd.cFileName;
                StringVector tmp = listFiles(path, true);
                for(string t : tmp)
                    lsFiles.push_back(t);
            }
            lsFiles.push_back(string((char*) fd.cFileName));
        }

    #else
        struct dirent *ent;
        if ((dir = opendir(pwd)) != NULL) {
            while ((ent = readdir(dir)) != NULL)
                lsFiles.push_back(ent->d_name);
            closedir(dir);
        }
    #endif
    return lsFiles;
}

StringVector filesWithExt(const string& pwd, const string& ext) {
    StringVector lsFiles = listFiles(pwd, false);
    StringVector out;
    for (string& file : lsFiles) {
        if (inString(file, ext)) 
            out.push_back(file);
    }
    return out;
}