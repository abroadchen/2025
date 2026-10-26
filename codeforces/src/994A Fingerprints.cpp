//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
外层循环遍历 t 的每个元素 t[i]。
内层循环让 t[i] 与 v 中每个元素 v[j] 比较。
一旦相等（t[i] == v[j]），就输出 t[i] 并跟一个空格。
效果：输出所有同时出现在 t 和 v 中的数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= (n); ++i)
using namespace std;

constexpr int N = 15;

int n, m, i, j, t[N], v[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> t[i];
    rep(i,m) cin >> v[i];
    rep(i,n) rep(j,m) if (t[i] == v[j]) cout << t[i] << ' ';
    return 0;
}