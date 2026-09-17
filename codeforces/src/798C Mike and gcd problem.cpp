//
// Created by Psy.C on 2026/9/17.
//
/**
求最大公约数
若 a%b != 0，递归 gcd(b, a%b)；否则返回 b
读入 n 个数到 a[1..n]
计算整个数组的最大公约数 k。
先输出 "YES"（表示可行）。
若 k > 1：所有数的 gcd 大于 1，则…… 输出 0 直接结束。
把每个数简化成奇偶标记：奇数标 1，偶数标 2
遍历每个相邻对 (a[i-1], a[i])。
若两个都是奇数：操作代价 +1，并把这两个位置都标记为偶数（2）
若相邻两个奇偶性不同（一个奇数一个偶数，异或为 1）：
操作代价 +2。
把两个位置都标为偶数
输出最少总操作次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(int a, int b) {
    return a%b ? gcd(b, a%b) : b;
}

constexpr int N = 1e5+7;
int a[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int k = gcd(a[1], a[2]);
    for (int i = 3; i <= n; ++i) k = gcd(k, a[i]);
    cout << "YES\n";
    if (k > 1) { cout << "0\n"; return 0; }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i]&1) a[i] = 1;
        else a[i] = 2;
    }
    for (int i = 2; i <= n; ++i)
        if (a[i]%2 && a[i-1]%2) { ++ans; a[i] = a[i-1] = 2; }
    for (int i = 2; i <= n; ++i)
        if ((a[i]%2)^(a[i-1]%2)) {
            ans += 2;
            a[i] = a[i-1] = 2;
        }
    cout << ans << '\n';
    return 0;
}