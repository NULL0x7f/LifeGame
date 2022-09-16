/*
 * file name: base_utility.h
 * author: X_js
 * description: the basic utility.
 * update time: 2022/9/1 8:50
 */
#ifndef _BASE_UTILITY_H_
#define _BASE_UTILITY_H_

#include <conio.h>
#include <sys/stat.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

enum Error_code {
    success,
    fail,
    range_error,
    underflow,
    overflow
};

#endif