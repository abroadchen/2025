//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
从 -1000 到 1000 枚举候选方向 i，跳过 0。
对每个 i，sum 统计满足 a[j]*i > 0 的元素个数——即符号与 i 相同的元素数量（a[j] 与 i 同号，乘积才 >0）。
若 2*sum >= n（即 sum ≥ ⌈n/2⌉，超过半数），说明符号与 i 相同的元素占多数，输出 i 并结束。
所有非零 i 都不满足则输出 0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 110, inf = 1e3;
int n, a[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    for (int i = -inf; i <= inf; i++) {
        if (i == 0) continue;
        int sum = 0;
        rep(j,n) if (a[j]*i > 0) sum++;
        if (2*sum >= n) { cout << i; return 0; }
    }
    cout << 0;
    return 0;
}