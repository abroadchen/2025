//
// Created by Psy.C on 2025/9/10.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    string start, target;
    cin >> start >> target;

    int start_x = start[0] - 'a';
    int start_y = start[1] - '1';
    int target_x = target[0] - 'a';
    int target_y = target[1] - '1';

    int dx = target_x - start_x;
    int dy = target_y - start_y;

    int moves = max(abs(dx), abs(dy));
    cout << moves << "\n";

    for (int i = 0; i < moves; i++) {
        string move = "";
        if (dx > 0) {
            move += "R";
            dx--;
        } else if (dx < 0) {
            move += "L";
            dx++;
        }

        if (dy > 0) {
            move += "U";
            dy--;
        } else if (dy < 0) {
            move += "D";
            dy++;
        }
        cout << move << "\n";
    }
    return 0;
}
