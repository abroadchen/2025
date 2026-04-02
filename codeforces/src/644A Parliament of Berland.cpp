//
// Created by Psy.C on 2026/4/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, a, b, mp[N][N];
int main() {
    fast;
    cin >> n >> a >> b;
    if (a*b < n) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 1, x = 1, y = 1; i <= n; ++i) {
        mp[x][y] = i;//将数字i填入位置(x,y)
        if (x&1) {
            y++;// 向右移动
            //如果超出右边界，向下移动一行，y保持在最右边
            if (y > b) { x++; y = b; }
        } else {
            y--;//向左移动
            //如果超出左边界，向下移动一行，y保持在最左边
            if (y <= 0) { x++; y = 1; }
        }
    }
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (j > 1) cout << ' ';
            cout << mp[i][j];
        }
        cout << '\n';
    }
    return 0;
}