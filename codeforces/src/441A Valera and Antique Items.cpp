//
// Created by Psy.C on 2026/2/8.
//
/**
n: 要处理的项目/组的数量
v: 比较的阈值
h[N]: 布尔数组，标记哪些项目满足条件（0或1）

O（所有项目中子项目的总数）
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000
using namespace std;


int main() {
    fast;
    int n, v; cin >> n >> v;
    int h[N]{}, i, k;
    for (i = 1; i <= n; ++i) {
        cin >> k;//项目i的子项目的数量
        for (int j = 0, s; j < k; ++j) {
            cin >> s;//每个子项目值
            if (s < v) h[i] = 1;
        }
    }
    int cnt = 0;
    for (i = 1; i <= n; ++i) if (h[i]) ++cnt;//满足条件的项目数量
    cout << cnt << '\n';
    for (i = 1; i < n; ++i) if (h[i]) cout << i << ' ';
    if (h[n]) cout << n;
    cout << '\n';
    return 0;
}