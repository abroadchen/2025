//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
p[i]：前 i 段工作量之和 对 n 取模（环形位置）。
s[i] 初始也等于这个模值，后面会被改写。
sum：总工作量 = h[1..m] 之和
h[i] 段工作量在环形上对应 p[i]（前缀和 mod n）
s[1..m] 原本是 m 个模位置，排序后做差分，得到 m 段间隔。
差分和刚好等于 n（回到 0 / n 起点），把环形切成 m 段弧长
(sum+n-1)/n 是 ceil(sum/n) = 所需的最少轮数。
输出每段弧长 s[1..m]
top 是当前要分配给的编号（从 1 开始，最多到 m）。
每轮 m 次，分别消耗每段弧长 s[i]，并输出当前 top。
当某个编号 top（非 m）的配额 h[top] 被扣到 ≤0，top 后移，直到处理完 h[m]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
using namespace std;

constexpr int N = 1e6+5;
int n, m, h[N], p[N], s[N], sum;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> h[i];
    rep(i,m-1) s[i] = p[i] = (p[i-1]+h[i])%n, sum += h[i];
    p[m] = s[m] = n, sum += h[m];
    sort(s+1,s+m+1);
    for (int i = m; i > 1; i--) s[i] -= s[i-1];
    cout << (sum+n-1)/n << '\n';
    rep(i,m) cout << s[i] << ' ';
    cout << '\n';
    int top = 1;
    while (h[m] > 0) {
        rep(i,m) {
            cout << top << ' ';
            h[top] -= s[i];
            if (top != m && h[top] <= 0) top++;
        }
        cout << '\n';
    }
    return 0;
}