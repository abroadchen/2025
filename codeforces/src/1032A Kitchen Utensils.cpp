//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
a[x]++：值域计数数组，a[x] 记录数值 x 出现的次数（这里值域只用 1-100）
读入 n 个数，每读一个：对应值的计数 +1，并更新 mx = 最大的出现次数
cnt = 出现过多少个不同的值（a[i] != 0 为真加 1）
先把 mx 向上取整到最近的 m 的倍数（不足则 +1，直到能被 m 整除）。
输出 cnt * mx - n
在所有值按最大频率 mx 配满的前提下，需要补足 cnt*mx - n 个名额
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    int mx = 0;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        a[x]++; mx = max(mx, a[x]);
    }
    int cnt = 0;
    for (int i = 1; i <= 100; i++) cnt += a[i] != 0;
    while (mx%m != 0) mx++;
    cout << cnt*mx-n << '\n';
    return 0;
}