//
// Created by Psy.C on 2025/9/10.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> board(3);
    for (int i = 0; i < 3; i++) {
        cin >> board[i];
    }

    int countX = 0, count0 = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') countX++;
            else if (board[i][j] == '0') count0++;
        }
    }

    if (countX < count0 || countX > count0 + 1) {
        cout << "illegal\n";
        return 0;
    }

    bool xWins = false, oWins = false;
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') xWins = true;
        if (board[i][0] == '0' && board[i][1] == '0' && board[i][2] == '0') oWins = true;
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == 'X' && board[1][j] == 'X' && board[2][j] == 'X') xWins = true;
        if (board[0][j] == '0' && board[1][j] == '0' && board[2][j] == '0') oWins = true;
    }

    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') xWins = true;
    if (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0') oWins = true;
    if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') xWins = true;
    if (board[0][2] == '0' && board[1][1] == '0' && board[2][0] == '0') oWins = true;

    if (xWins && oWins) {
        cout << "illegal\n";
        return 0;
    }

    if (xWins) {
        if (countX == count0 + 1) {
            cout << "the first player won\n";
        } else {
            cout << "illegal\n";
        }
        return 0;
    }

    if (oWins) {
        if (countX == count0) {
            cout << "the second player won\n";
        } else {
            cout << "illegal\n";
        }
        return 0;
    }

    if (countX + count0 == 9) {
        cout << "draw\n";
        return 0;
    }

    if (countX == count0) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
    return 0;

}