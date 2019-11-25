#include <iostream>

using namespace std;

class TikTacToe {
    char** board;
    int width;
    bool isAWinner;
    char winner;
public:
    // Constructor
    TikTacToe(int numRows);

    //Functions
    int getWidth() { return this->width; }

    bool hasWinner();
    void printBoard();

    void getMove(int &row, int &col, char letter);
    void makeMove(char letter, int row, int col);

    char getWinner();

private: 
    //Private Helper Functions
    bool spotIsAvailable(int row, int col);
    bool checkForWinner();

};

////////////////////////////////////////////////////////////
//                      Constructor                       //
////////////////////////////////////////////////////////////
TikTacToe::TikTacToe(int numRows) {
    width = numRows;
    this->isAWinner = false;
    winner = 'C';

    //Initialize the board.
    board = new char* [numRows];
    for(int i = 0; i < numRows; ++i) {
        board[i] = new char[numRows];
    }

    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numRows; ++j) {
            board[i][j] = ' ';
        }
    }
}

/////////////////////////////////////////////////////////////
//                  Helper Functions                       //
////////////////////////////////////////////////////////////
bool TikTacToe::spotIsAvailable(int row, int col) {
    return board[row][col] == ' ' ? true : false; 
}

/////////////////////////////////////////////////////////////
//                  Different Win Checks                   //
////////////////////////////////////////////////////////////

bool wonInRow(int row, int width, char** board) {
    char farLeft = board[row][0];

    if(farLeft == ' ') {
        return false;
    }
    for(int j = 1; j < width; ++j) {
        char current = board[row][j];
        if(current != farLeft) {
            return false;
        }
    }
    return true;
}

bool wonInCol(int col, int width, char** board) {
    char top = board[0][col];
    if(top == ' ') {
        return false;
    }
    for(int j = 1; j < width; ++j) {
        char current = board[j][col];
        if(current != top) {
            return false;
        }
    }
    return true;
}

bool wonDiagLeft(int width, char** board) {
    char start = board[0][width - 1]; 
    for(int i = 1; i < width; ++i) {
        if(start == ' ') {
            return false;
        }
        char current = board[i][width - 1 - i];
        if(current != start) {
            return false;
        }
    }
    return true;
}

bool wonDiagRight(int width, char** board) {
    char start = board[0][0];
    for(int i = 1; i < width; ++i) {
        if(start == ' ') {
            return false;
        }
        char current = board[i][i];
        if(current != start) {
            return false;
        }
    }
    return true;
}

bool TikTacToe::checkForWinner() {
    //Check all of a row is the same
    for(int i = 0; i < width; ++i) {
       if(wonInRow(i, width, board)) {
           return true;
       }
    }
    //Check all the same col
    for(int i = 0; i < width; ++i) {
        if(wonInCol(i, width, board)) {
            return true;
        }
    }
    //Check diagonal to right
    if(wonDiagRight(width, board)) {
        return true;
    }
    //Check diagonal to left
    if(wonDiagLeft(width, board)) {
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////
//                  Public Functions                       //
////////////////////////////////////////////////////////////

bool TikTacToe::hasWinner() {
    return isAWinner;
}

void TikTacToe::printBoard() {
    cout << endl;
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < width; ++j) {
            if(j == width - 1) {
                cout << " " << board[i][j] << " ";
            } else {
                cout << " " << board[i][j] << " |";
            }
        }
        cout << endl;
        if(i < width - 1) {
            for(int i = 0; i < (width * 3) + (1 * width); ++i) {
                cout << '-';
            }
        }
        cout << endl;
    }
}

void TikTacToe::getMove(int &row, int &col, char letter) {
    bool goodAnswer = false;
    while(!goodAnswer) {
        cout << "Enter row, col for " << letter << ": ";
        cin >> row >> col;
        if((row > width - 1 || col > width - 1) || (row < 0 || col < 0)) {
            cout << "That is out of bounds." << endl;
            goodAnswer = false;
            continue;
        }
        if(!spotIsAvailable(row, col)) {
            cout << "Position taken" << endl;
            goodAnswer = false;
            continue;
        }
        goodAnswer = true;
    }
    
}

void TikTacToe::makeMove(char letter, int row, int col) {
    board[row][col] = letter;
    if(checkForWinner()) {
        isAWinner = true;
        winner = letter;
    }
}


char TikTacToe::getWinner() {
    return isAWinner ? this->winner : 'C';
}


/////////////////////////////////////////////////////////////
//                   Functions                             //
//  These are for neccesary Functions not a part of       //
//                  TikTacToe                             //
////////////////////////////////////////////////////////////

int getRows() {
    int rows;
    bool good = false;
    while(!good) {
        cout << "Enter in a number of rows: " << endl;
        cin >> rows;
        if(!cin) {
            cin.clear();
            while (cin.get() != '\n') continue;
            cout << "That isnt a good number. Try a new one between 3 and 9." << endl;
            good = false;
            continue;
        } else if(rows > 9 || rows < 3) {
            cout << "That isnt a good number. Try a new one between 3 and 9." << endl;
            good = false;
            continue;
        } else {
            good = true;
        }
    }

    return rows;
}