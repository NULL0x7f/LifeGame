/*
 * file name: life.cpp
 * author: X_js
 * description: the implement of Life class.
 * update time: 2022/9/1 9:58
 */
#ifndef _LIFE_CPP_
#define _LIFE_CPP_

#include "life.h"

#include "file_utility.hpp"
#include "random_utility.hpp"

using std::ifstream;
using std::ofstream;

Life::Life() {
    for (int i = 0; i <= maxrow + 1; i++)
        for (int j = 0; j <= maxcol + 1; j++)
            grid[i][j] = 0;  // initialize every cell with 0
}

int Life::neighborCount(int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++)
        for (int j = col - 1; j <= col + 1; j++)
            if (i != row || j != col)
                count += grid[i][j];
    return count;
}

void Life::success(string s) {
    cout << s << " success!" << endl;
    print();
}

bool Life::checkOutOfRange(int row, int col) {
    // check the row is out of range
    if (row < 1 || row > maxrow) {
        cout << "row " << row << " is out of range" << maxrow << "." << endl;
        return false;
    }

    // check the col is out of range
    if (col < 1 || col > maxcol) {
        cout << "col " << col << " is out of range" << maxcol << "." << endl;
        return false;
    }
    return true;
}

bool Life::initializeWithLivingCellCoordinate() {
    cout << "do you want to initialize from file? (y/n)" << endl;
    cout << "if you do, press 'y' or 'Y'. otherwise, press 'n' or 'N'." << endl;
    char fileOpt = getch();
    while (fileOpt != 'y' && fileOpt != 'Y' && fileOpt != 'n' && fileOpt != 'N') {
        // if press other character, tell user and receive a character again.
        cout << "if you do, press 'y' or 'Y'. otherwise, press 'n' or 'N'." << endl;
        fileOpt = getch();
    }
    ifstream in;
    if (fileOpt == 'y' || fileOpt == 'Y') {
        // if user want to initialize from file, ask user the filename.
        in.open(askFile());
    } else {
        // else, remind user input content.
        in.open("CON");
        cout << "List the coordinate of living cells." << endl;
        cout << "Terminate the list with the special pair (-1, -1)." << endl;
    }
    int row, col;
    while (true) {
        // if read fail from file, remind user and restart game.
        if (!(in >> row >> col)) {
            cout << "unable to end reading normally!" << endl;
            return false;
        }
        // check is the list end
        if (row == -1 && col == -1) {
            break;
        }

        // check is the coordinate out of range
        if (!checkOutOfRange(row, col))
            continue;

        grid[row][col] = 1;
    }
    success("initialize");
    in.close();
    return true;
}

bool Life::initializeWithPattern() {
    cout << "do you want to initialize from file? (y/n)" << endl;
    cout << "if you do, press 'y' or 'Y'. otherwise, press 'n' or 'N'." << endl;
    char fileOpt = getch();
    while (fileOpt != 'y' && fileOpt != 'Y' && fileOpt != 'n' && fileOpt != 'N') {
        cout << "if you do, press 'y' or 'Y'. otherwise, press 'n' or 'N'." << endl;
        fileOpt = getch();
    }
    ifstream in;
    if (fileOpt == 'y' || fileOpt == 'Y') {
        in.open(askFile());
    }
    if (fileOpt == 'n' || fileOpt == 'N') {
        in.open("CON");
        cout << "input a grid with " << maxrow << " rows and " << maxcol << " cols, use '_' to denote dead cell and 'O' to denote living cell." << endl;
    }
    char str[maxcol + 1];
    for (int i = 1; i <= maxrow; i++) {
        in.getline(str, maxcol + 1);
        for (int j = 0; j < maxcol; j++) {
            if (str[j] == 'O')
                grid[i][j + 1] = 1;
            else if (str[j] == '_')
                grid[i][j + 1] = 0;
            else {
                cout << "you input a illegal character. the game will restart." << endl;
                in.close();
                return false;
            }
        }
    }
    success("initialize");
    in.close();
    return true;
}

void Life::initializeRandom() {
    double density;
    cout << "please enter a real number from 0 to 1 denote the density of living cells." << endl;
    cin >> density;
    while (density < 0 || density > 1) {
        cout << "please enter a real number from 0 to 1!" << endl;
        cin >> density;
    }
    for (int i = 1; i <= maxrow; i++)
        for (int j = 1; j <= maxcol; j++)
            // generate a real number from 0 to 1 randomly, if it is less than density, the cell is initialized to living.
            grid[i][j] = (randomDouble() <= density);
    success("initialize");
}

void Life::print() {
    cout << "the current configuration is:" << endl;
    for (int i = 1; i <= maxrow; i++, puts(""))
        for (int j = 1; j <= maxcol; j++)
            cout << (grid[i][j] == 1 ? 'O' : '_') << " ";
}

void Life::update() {
    int new_grid[maxrow + 2][maxcol + 2];
    for (int i = 1; i <= maxrow; i++) {
        for (int j = 1; j <= maxcol; j++) {
            int count = neighborCount(i, j);
            // if it is living, and there are 2 or 3 living cells around it, it will be still living, otherwise it will be dead.
            // if it is dead, and there are exactly 3 living cells around it, it will be living, otherwise it will be still dead.
            new_grid[i][j] = ((grid[i][j] == 1 && count >= 2 && count <= 3) || (grid[i][j] == 0 && count == 3));
        }
    }
    for (int i = 1; i <= maxrow; i++) {
        for (int j = 1; j <= maxcol; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
    success("update");
}

void Life::modifyCell() {
    cout << "please enter 2 numbers denote the coordinate of the cell to be modified." << endl;
    int row, col;
    cin >> row >> col;
    while (!checkOutOfRange(row, col)) {
        cin >> row >> col;
    }
    cout << "please enter 0 or 1 denote the state the cell to be, and 0 denotes dead, 1 denotes living." << endl;
    cout << "[ 0 ] dead." << endl;
    cout << "[ 1 ] living." << endl;
    char opt = getch();
    while (opt != '0' && opt != '1') {
        cout << "please enter number 0 or 1." << endl;
        opt = getch();
    }
    grid[row][col] = opt - '0';
    success("modify");
}

void Life::save() {
    ofstream fout("output.txt");
    for (int i = 1; i <= maxrow; i++, fout << endl)
        for (int j = 1; j <= maxcol; j++)
            fout << (grid[i][j] == 1 ? 'O' : '_');
    cout << "current configuration has been exported to \"output.txt\"" << endl;
    fout.close();
}
#endif