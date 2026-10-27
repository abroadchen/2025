//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
n：数的个数
mn：当前最小值
sum：所有数之和
p：最小值所在下标
一边累加 sum，一边记录最小值 mn 与它首次出现的下标 p
sum - mn <= mn → 其余数之和 ≤ 最小值
可行时，输出 n-1，然后输出除最小值下标 p 之外的所有下标
若"总和 − 最小值 ≤ 最小值"则无解；否则一定可行，构造为把最小值放在序列最后一位，其余 n−1 个数按任意（此处为原序）排在前面——因为其余数之和不小于其任意前缀，能保证放最小值时前面和仍为正，从而每个前缀和 > 0。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int inf = 0x3f3f3f3f;
int n, mn, sum, p;
int main() {
    fast;
    cin >> n; mn = inf;
    for (int i = 1, x; i <= n; i++) {
        cin >> x; sum += x;
        if (x < mn) { p = i; mn = x; }
    }
    if (sum - mn <= mn) { cout << "-1\n"; return 0; }
    cout << n-1 << '\n';
    for (int i = 1; i <= n; i++)
        if (i != p) cout << i << ' ';
    return 0;
}