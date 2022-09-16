/*
 * file name: life.h
 * author: X_js
 * description: the definition of Life class.
 * update time: 2022/9/1 8:17
 */
#ifndef _LIFE_H_
#define _LIFE_H_

#include "base_utility.h"

const int maxrow = 40, maxcol = 80;  // the grid has 40 rows and 80 cols

class Life {
private:
    int grid[maxrow + 2][maxcol + 2];
    int neighborCount(int, int);     // count how many living cells around the cell in (row, col)
    void success(string);            // show user the success message and print current configuration
    bool checkOutOfRange(int, int);  // check is the given coordinate out of range

public:
    Life();
    bool initializeWithLivingCellCoordinate();  // initialize with given living cells coordinates
    bool initializeWithPattern();               // initialize with the pattern consist of cells
    void initializeRandom();                    // initialize randomly with given density of living cells, gospel of lazy people
    void print();                               // print current configuration
    void update();                              // generate new configuration base on current configuration
    void modifyCell();                          // change one cell's life to living or dead
    void save();                                // export current configuration to a file
};

#endif