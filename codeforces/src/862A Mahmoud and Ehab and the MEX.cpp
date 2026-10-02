//
// Created by Psy.C on 2026/10/2.
//
/***
读入 n 个数 v，把 t[v] 标记为 true（即第 v 个"会话/时间/频道"出现过）。
t[] 是布尔数组，下标范围 0..104
先数 0,1,...,m-1 这些下标里没有被标记的个数（!t[i]）；
再检查下标 m 是否被标记（t[m]），是则 ans+1；
输出 ans
若 t[0] 为真 → 输出 1，否则输出 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    bool t[105]{};
    for (int i = 0, v; i < n; ++i) {
        cin >> v; t[v] = true;
    }
    if (m > 0) {
        int ans = 0;
        for (int i = 0; i < m; ++i)
            if (!t[i]) ans++;
        if (t[m]) ans++;
        cout << ans << '\n';
    } else {
        if (t[0]) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}