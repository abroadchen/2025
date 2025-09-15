//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char grid[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cin >> grid[i][j];
    }

    bool symmetric = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != grid[2 - i][2 - j]) {
                symmetric = false;
                break;
            }
        }
        if (!symmetric) break;
    }

    if (symmetric) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}