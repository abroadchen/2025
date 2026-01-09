//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int r, c, row[11]={}, col[11]={}; cin >> r >> c; string s;
    for (int i = 0; i < r; ++i) {
        cin >> s;
        for (int j = 0; j < c; ++j) if (s[j] == 'S') {
            row[i] = 1; col[j] = 1;//标记第i行和第j列为已覆盖
        }
    }
    int ans = 0;
    for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) {
        if (row[i] == 0 || col[j] == 0) ans += 1;//至少有一个没有被覆盖
    }
    cout << ans << '\n';
    return 0;
}