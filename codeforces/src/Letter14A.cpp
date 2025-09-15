//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    int min_row = n, max_row = -1;
    int min_col = m, max_col = -1;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                min_row = min(min_row, i);
                max_row = max(max_row, i);
                min_col = min(min_col, j);
                max_col = max(max_col, j);
            }
        }

    for (int i = min_row; i <= max_row; ++i) {
        for (int j = min_col; j <= max_col; ++j)
            cout << grid[i][j];
        cout << "\n";
    }
    return 0;
}