//
// Created by Psy.C on 2026/10/18.
//
/**
这里有个关键正确性细节 / 潜在 bug：a[i] == b[j] && j <= m 中，C++ 的 && 短路求值——先算 a[i]==b[j]（若 j 已越界为 b[m+1]，是未定义行为/越界读），再算 j<=m。严格说应该写成 j <= m && a[i]==b[j]（先判界再访问）。不过由于 b[m+1] 初始为 0，若 a[i] 也正好等于 0 可能误判；否则通常碰巧安全，但这是未定义行为，理论上有隐患
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N], b[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,n) cin >> a[i], a[i] += a[i-1];
    rep(i,1,m) cin >> b[i], b[i] += b[i-1];
    int j = 1, ans = 0;
    rep(i,1,n) {
        while (j <= m && a[i] > b[j]) j++;//b后移直到 b[j] >= a[i]
        ans += a[i] == b[j] && j <= m;//若相等则计数
    }
    cout << ans << '\n';
    return 0;
}