//
// Created by Psy.C on 2026/3/29.
//
/**
r[i].first: 行i最后一次更新的值
r[i].second: 行i最后一次更新的操作时间戳
c[j].first: 列j最后一次更新的值
c[j].second: 列j最后一次更新的操作时间戳
op == 1: 更新第x行的所有元素为y
op == 2: 更新第x列的所有元素为y
时间戳i用于判断哪个操作更新

如果行i和列j都没有被更新过：值为0
如果只有行i被更新过：值为行i的最新值
如果只有列j被更新过：值为列j的最新值
如果行i和列j都被更新过：值为最后更新的那个（时间戳更大）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e3+5;
int n, m, q;
ii r[N], c[N];
int main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) r[i].first = 0;
    for (int i = 1; i <= m; ++i) c[i].first = 0;
    for (int i = 1, op, x, y; i <= q; ++i) {
        cin >> op >> x >> y;
        if (op == 1) {
            r[x].first = y; r[x].second = i;
        } else {
            c[x].first = y; c[x].second = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) cout << ' ';
            if (r[i].first == 0 && c[j].first == 0) cout << 0;
            else if (r[i].first == 0) cout << c[j].first;
            else if (c[j].first == 0) cout << r[i].first;
            else {
                if (r[i].second > c[j].second) cout << r[i].first;
                else cout << c[j].first;
            }
        }
        cout << '\n';
    }
    return 0;
}