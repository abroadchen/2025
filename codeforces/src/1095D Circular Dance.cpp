//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
a[i][0]、a[i][1] 是第 i 个点的两个邻居
从点 1 开始。
点 1 的两个邻居是 a[1][0] 和 a[1][1]，暂时先按 1 → a[1][0] → a[1][1] 排。
但这两个邻居谁在前谁在后不确定（可能顺序反了）
判断 p[3] 是否真的是 p[2] 的邻居（即 a[p[2]][0] 或 a[p[2]][1]）。
若不是，说明顺序反了，交换 p[2]、p[3]。
这样保证 p[1]-p[2]-p[3] 是一条真正的路径（点 1 在中间，2 和 3 是它的两个邻居）
已知 p[i-2] 的两个邻居 a[p[i-2]][0] 和 a[p[i-2]][1]，其中一个是 p[i-1]（已在环上），另一个就是 p[i]。
因为总和 - 已知邻居 = 另一个邻居：
p[i] = (a[p[i-2]][0] + a[p[i-2]][1]) - p[i-1]。
逻辑：p[i-2] 在环上的两个邻居是紧邻它的 p[i-1]（左边）和 p[i]（右边），从它的邻居集合里去掉了 p[i-1]，剩下的就是 p[i]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;

int n, a[N][2], p[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i][0] >> a[i][1];
    p[1] = 1; p[2] = a[1][0]; p[3] = a[1][1];
    if (p[3] != a[p[2]][0] && p[3] != a[p[2]][1]) swap(p[2],p[3]);
    for (int i = 4; i <= n; i++) p[i] = a[p[i-2]][0]+a[p[i-2]][1]-p[i-1];
    rep(i,n) cout << p[i] << ' ';
    return 0;
}