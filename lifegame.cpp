/*
 * file name: lifegame.cpp
 * author: X_js
 * description: the main program of life game.
 * update time: 2022/9/1 9:01
 */

#include "life.cpp"

void instructions() {
    ifstream fin("readme.txt");
    const int LINE_LENGTH = 1000;
    char s[LINE_LENGTH];
    while (fin.getline(s, LINE_LENGTH)) {
        cout << s << endl;
    }
    fin.close();
}

bool work(Life &configuration) {
    cout << " [ 1 ] modify a cell's life." << endl;
    cout << " [ 2 ] save current configuration to a file." << endl;
    cout << " [ SPACE ] generate next configuration." << endl;
    cout << " [ 0 ] restart the game." << endl;
    cout << "please enter a number from 0 to 2 or press space key to denote your option." << endl
         << endl;
    char opt = getch();
    switch (opt) {
    case '0':
        return false;
        break;
    case '1':
        configuration.modifyCell();
        break;
    case '2':
        configuration.save();
        break;
    case ' ':
        configuration.update();
        break;
    default:
        cout << "please enter a number from 0 to 2 or press the space key." << endl;
        return true;
        break;
    }
    return true;
}

bool startGame() {
    Life configuration;

    // print game start message.
    cout << "---------------------- Game Start ----------------------" << endl;
    cout << " [ 1 ] initialize by listing the coordinates of living cells." << endl;
    cout << " [ 2 ] initialize with pattern using '_' to denote dead cell and 'O' to denote living cell." << endl;
    cout << " [ 3 ] initialize randomly." << endl;
    cout << " [ 0 ] exit the program." << endl;
    cout << "please enter a number from 0 to 4 to denote your option." << endl
         << endl;

    // get the user's choice.
    char opt = getch();
    switch (opt) {
    case '0':
        return false;
        break;
    case '1':
        if (!configuration.initializeWithLivingCellCoordinate())
            return true;
        break;
    case '2':
        if (!configuration.initializeWithPattern())
            return true;
        break;
    case '3':
        configuration.initializeRandom();
        break;
    default:
        cout << "please enter a number from 0 to 4" << endl;
        return true;
        break;
    }

    // operator the configuration repeatly.
    while (work(configuration))
        ;
    return true;
}

int main() {

    // initialize for random.
    initRandom();

    // print instruction to cmd.
    instructions();

    // start game repeatly.
    while (startGame())
        ;
    return 0;
}