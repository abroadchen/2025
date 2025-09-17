//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<string> flag(n);
    for (int i = 0; i < n; ++i) cin >> flag[i];

    bool valid = true;
    for (int i = 0; i < n; ++i) {
        char first_color = flag[i][0];
        for (int j = 0; j < m; ++j)
            if (flag[i][j] != first_color) {
                valid = false;
                break;
            }
        if (!valid) break;
    }

    if (valid) {
        for (int i = 0; i < n - 1; ++i)
            if (flag[i][0] == flag[i + 1][0]) {
                valid = false;
                break;
            }
    }
    if (valid) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}