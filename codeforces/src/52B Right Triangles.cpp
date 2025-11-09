//
// Created by Psy.C on 2025/10/15.
//
/*
 *
*r(n, 0): 大小为 n，初始值都为 0，用于记录每行中 '*' 的数量
c(m, 0): 大小为 m，初始值都为 0，用于记录每列中 '*' 的数量
 *
*双重循环遍历整个网格：
外层循环遍历行（i 从 0 到 n-1）
内层循环遍历列（j 从 0 到 m-1）
如果当前位置是 '*'，则对应行计数 r[i] 和列计数 c[j] 都加 1
 *
*再次双重循环遍历整个网格：
对于每个 '*' 位置，计算 (r[i] - 1) * (c[j] - 1) 并累加到 ans 中
r[i] - 1 表示同一行中其他 '*' 的数量
c[j] - 1 表示同一列中其他 '*' 的数量
这个乘积表示以当前位置为交点能形成的十字架数量
 *
 */
#include <ios>
#include <iostream>
#include <vector>
#include <string>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<string> g(n);
    rep(i,n) cin >> g[i];

    vector<ll> r(n, 0), c(m, 0);
    rep(i,n) rep(j,m) if (g[i][j] == '*') { r[i]++; c[j]++; }
    ll ans(0);
    rep(i,n) rep(j,m) if (g[i][j] == '*') ans += (r[i] - 1) * (c[j] - 1);
    cout << ans << '\n';
    return 0;
}