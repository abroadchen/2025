//
// Created by Psy.C on 2026/4/28.
//
/**
n: 表示序列长度或节点数
m: 表示区间数量
循环m次，每次读入区间左端点l和右端点r
计算每个区间的长度（r-l+1）
更新mn为所有区间长度中的最小值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int mn = 1e9;
    for (int i = 0, l, r; i < m; ++i)
        cin >> l >> r, mn = min(mn, r - l +1);
    cout << mn << '\n';
    for (int i = 0; i < n; ++i)
        cout << (i%mn) << " \n"[i==n-1];
    return 0;
}