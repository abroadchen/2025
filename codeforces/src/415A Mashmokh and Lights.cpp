//
// Created by Psy.C on 2026/2/3.
//
/*
* 最坏情况：O(m×n)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, f[110]={}; cin >> n >> m;
    for (int i = 1, k; i <= m; ++i) {
        cin >> k;
        for (int j = k; j <= n; ++j) {
            if (!f[j]) f[j] = k;//如果位置 j 还没被占用，就赋值为 k
            else break;
        }
    }
    for (int i = 1; i <= n; ++i) cout << f[i] << ' ';
    return 0;
}