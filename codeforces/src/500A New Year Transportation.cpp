//
// Created by Psy.C on 2026/2/23.
//
/**
p表示当前位置，初始为0
当当前位置p小于目标位置(t-1)时，从位置p跳跃c[p]步
这是一个贪心策略：每次都选择当前能跳的最大步数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, t, p;
int main() {
    fast;
    cin >> n >> t;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];
    while (p < t - 1) p += c[p];
    if (p == t - 1) cout << "YES\n"; else cout << "NO\n";
    return 0;
}