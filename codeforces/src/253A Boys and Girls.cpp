//
// Created by Psy.C on 2025/12/17.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, m, i, j, mn, mx; cin>>n>>m;
    vector<char> b(n), g(m);
    for (i = 0; i < n; ++i) b[i] = 'B';
    for (i = 0; i < m; ++i) g[i] = 'G';
    if (n > m) {
        mn = m;
        for (i = 0, j = 0; i < mn && j < mn; ++i, ++j) {
            cout << b[i] << g[j];//BG交替输出，共输出m对
        }
        mx = n;
        for (i = mn; i < mx; ++i) cout << b[i];//(n-m)个'B'没有配对，需要单独输出
    } else if (m >= n) {
        mn = n;
        for (i = 0, j = 0; i < mn && j < mn; ++i, ++j) {
            cout << g[j] << b[i];//GB交替输出，共输出n对
        }
        mx = m;
        for (i = mn; i < mx; ++i) cout << g[i];//(m-n)个'G'没有配对
    }
    return 0;
}