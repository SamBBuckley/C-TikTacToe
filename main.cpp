#include <iostream>
#include "TicTakToe.h"

using namespace std;

// Re-creation of main in prompt.
int main() {

    char again = 'y';
    while(tolower(again) == 'y') {

        int numRows = 0;
        int turnNum = 0;

       numRows = getRows();

        TikTacToe game(numRows);

        do {
            game.printBoard();
            turnNum++;
            char curLetter;
            curLetter = (turnNum % 2 == 0) ? 'O' : 'X';
            int row, col;

            //This should ensure valid.
            game.getMove(row, col, curLetter);

            //Once known to be good
            game.makeMove(curLetter, row, col);


        } while(!game.hasWinner() && (turnNum != game.getWidth() * game.getWidth()));

        game.printBoard();
        char winner = game.getWinner();
        if(winner == 'C') {
            cout << "Cat!" << endl;
        } else {
            cout << winner << " wins!" << endl;
        }

        cout << "Do you want to play again? " << endl;
        cin >> again;

    }
}