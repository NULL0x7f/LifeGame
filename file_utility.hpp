/*
 * file name: file_utility.hpp
 * author: X_js
 * description: the utility for file.
 * update time: 2022/8/31 8:45
 */
#ifndef _FILE_UTILITY_HPP_
#define _FILE_UTILITY_HPP_

#include "base_utility.h"

// check is file in current directory.
bool isFileExist(const string &filename) {
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
}

// ask user input a filename.
string askFile() {
    cout << "please enter the filename." << endl;
    string s;
    getline(cin, s);
    while (!isFileExist(s)) {
        cout << "file doesn't exits." << endl;
        getline(cin, s);
    }
    return s;
}

#endif