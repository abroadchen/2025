//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
N：数组上界。
n：序列长度。
k：目标上限。
ans：不断用 gcd 累积的最大公约数（最终作为步长 d）。
a[]：序列
逐个读入 a[i]，并不断 ans = gcd(ans, a[i])。
最终 ans = 集合 {k, a1, a2, …, an} 的最大公约数，记为 d。
之所以初始为 k，是因为最终可生成的数还要受限于 ≤ k，步长应为 gcd(k, a…)。
cout << k/ans << '\n';

可输出的数共有 k/d 个：0·d, 1·d, …, (k/d - 1)·d（共 k/d 个，从 0 到 k-d）
输出 0, d, 2d, …, (k/d -1)·d，空格分隔

一次线性扫描：O(n)（gcd 每次 O(log值)）。
输出 O(k/d)。
总复杂度 O(n log V + k/d)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e5+5;

int gcd(int a, int b) { return b?gcd(b, a%b) : a; }

int n, k, ans, a[N];
int main() {
    fast;
    cin >> n >> k; ans = k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans = gcd(ans, a[i]);
    }
    cout << k/ans << '\n';
    for (int i = 0; i <= k/ans-1; i++) cout << i*ans << ' ';
    return 0;
}