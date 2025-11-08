//
// Created by Psy.C on 2025/9/12.
//


#include <iosfwd>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> board(8);
    for (int i = 0; i < 8; i++) cin >> board[i];

    int min_strokes = 16;

    for (int mask = 0; mask < (1 << 8); mask++) {
        int row_strokes = 0;
        vector<string> covered(8, "WWWWWWWW");

        for (int i = 0; i < 8; i++) {
            if (mask & (1 << i)) {
                row_strokes++;
                for (int j = 0; j < 8; j++) {
                    covered[i][j] = 'B';
                }
            }
        }

        int col_strokes = 0;
        for (int j = 0; j < 8; j++) {
            bool need_col = false;
            for (int i = 0; i < 8; i++) {
                if (board[i][j] == 'B' && covered[i][j] == 'W') {
                    need_col = true;
                    break;
                }
            }
            if (need_col) {
                col_strokes++;
                for (int i = 0; i < 8; i++) covered[i][j] = 'B';
            }
        }


        bool match = true;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] != covered[i][j]) {
                    match = false;
                    break;
                }
            }
            if (!match) break;
        }

        if (match) min_strokes = min(min_strokes, row_strokes + col_strokes);
    }

    cout << min_strokes << endl;
    return 0;
}