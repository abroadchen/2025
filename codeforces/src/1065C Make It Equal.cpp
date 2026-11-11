//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
循环读入 n, k。
每次清空 b[]。
读入每个高度 a[i]，并做频次统计：b[a[i]-1]++（b[h-1] 表示高度为 h 的物品数量）。
排序后 a[0] 是最矮、a[n-1] 是最高的。
特判：若最高等于最矮，说明所有物品已同高，直接输出 0，进入下一组。
c[i] 表示：从高度 i 往上所有高度（即高度 ≥ i 且 ≤ 最高高度）的物品总数。
从最高往下遍历，c[i] = c[i+1] + b[i]（后缀累加）。
含义：把高度从 i 降到 i-1 这"一层"，需要削的物品数量 = 高度 ≥ i 的物品总数
从最高层往最低层遍历，每"下降一层高度"需要的操作数就是 c[i]。
k 是每轮最多可做的操作数。
贪心：尽量把多个"层"的操作塞进同一轮；若 t + c[i] > k 装不下，就新开一轮，ans++，并把 t 重置为当层 c[i]。
初始 ans = 1（至少一轮，因为存在不同高度）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;

int n, k, a[N], b[N], c[N];
int main() {
    fast;
    while (cin >> n >> k) {
        memset(b, 0, sizeof b);
        for (int i = 0; i < n; i++) { cin >> a[i]; b[a[i]-1]++; }
        sort(a, a+n);
        if (a[0] == a[n-1]) { cout << 0 << '\n'; continue; }
        c[a[n-1]] = 0;
        for (int i = a[n-1]-1; i >= a[0]; i--) c[i] = c[i+1] + b[i];
        int ans = 1, t = 0;
        for (int i = a[n-1]-1; i >= a[0]; i--) {
            if (t + c[i] <= k) t += c[i];
            else { t = c[i]; ans++; }
        }
        cout << ans << '\n';
    }
    return 0;
}