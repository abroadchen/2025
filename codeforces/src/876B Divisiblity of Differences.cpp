//
// Created by Psy.C on 2026/10/6.
//
/**
读入 n（个数）、k（阈值）、m（模数）。
依次读入每个数到 a[i]。
b[a[i]%m] 是"余数为 a[i]%m"的出现次数，++b[...] 自增。
当某个余数的计数恰好达到 k 时，进入分支
输出 Yes。
从 j=1 扫描到当前 i，把所有模 m 余数等于当前数 a[i] 余数的数值依次输出（用空格分隔）。
输出完成后 return 0 结束程序
如果读完全部 n 个数后，没有任何余数计数达到 k，则输出 No
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e7+10;
int a[N], b[N];
int main() {
    fast;
    int n, k, m; cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (++b[a[i]%m] == k) {
            cout << "Yes\n";
            for (int j = 1; j <= i; ++j)
                if (a[j]%m == a[i]%m)
                    cout << a[j] << ' ';
            return 0;
        }
    }
    cout << "No";
    return 0;
}