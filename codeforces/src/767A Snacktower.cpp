//
// Created by Psy.C on 2026/9/7.
//
/**
a[i]：输入的第 i 个数。
vis[x]：标记数字 x 是否已经出现过（vis[k]==1 表示 k 已经输入过）
游标 t 从 n 开始（初始认为最大的数是 n)
只要从 t 指向的那个数是"已出现"的，就输出它，并把 t 减 1（继续往更小的数看
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;
int a[N], vis[N];
int main() {
    fast;
    int n; cin >> n;
    int t = n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vis[a[i]] = 1;
        for (; vis[t] == 1; --t) cout << t << ' ';
        cout << '\n';
    }
    return 0;
}