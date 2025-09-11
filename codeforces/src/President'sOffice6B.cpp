//
// Created by Psy.C on 2025/9/11.
//


#include <ios>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    char president_color;

    cin >> n >> m >> president_color;

    vector<vector<char>> office(n, vector<char>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> office[i][j];
    }
    set<char> deputies;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (office[i][j] == president_color) {
                if (i > 0 && office[i - 1][j] != '.' && office[i - 1][j] != president_color) deputies.insert(office[i - 1][j]);
                if (i < n - 1 && office[i + 1][j] != '.' && office[i + 1][j] != president_color) deputies.insert(office[i + 1][j]);
                if (j > 0 && office[i][j - 1] != '.' && office[i][j - 1] != president_color) deputies.insert(office[i][j - 1]);
                if (j < m - 1 && office[i][j + 1] != '.' && office[i][j + 1] != president_color) deputies.insert(office[i][j + 1]);
            }
        }
    }

    cout << deputies.size() << endl;
    return 0;
}