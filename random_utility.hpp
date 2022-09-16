/*
 * file name: random_utility.hpp
 * author: X_js
 * description: the utility for random.
 * update time: 2022/8/31 8:48
 */
#ifndef _RANDOM_UTILITY_HPP_
#define _RANDOM_UTILITY_HPP_

#include "base_utility.h"

// initialize for random.
void initRandom() {
    srand(time(NULL));
}

// return a random real number from 0 to 1
double randomDouble() {
    return (double)rand() / RAND_MAX;
}

#endif