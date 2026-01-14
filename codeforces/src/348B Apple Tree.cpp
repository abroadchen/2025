//
// Created by Psy.C on 2026/1/14.
//
/**
* ans：最终答案
mul[N]：每个节点的倍数因子
a[N]：每个节点的值
x：最小叶子值
lcm：最小公倍数
e[N]：邻接表存储树
 *
 *如果已经无解，直接返回
 *根节点的倍数因子为1
 *如果是叶子节点
 *更新最小叶子值
 *更新LCM
 *如果LCM超过最小值，无解
 *计算当前节点的子节点数量
 *递归处理子节点
 *
 *O(n * log(max_value))，主要是GCD计算的复杂度
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100007
#define inf (1ll<<60)
using namespace std;

ll gcd(const ll a, const ll b) { return !b ? a : gcd(b, a % b); }

ll ans, mul[N], a[N], x, lcm;
vector<int> e[N];
void dfs(const int u, const int p) {
    if (ans == -1) return;
    if (p == -1) mul[u] = 1;
    if (e[u].size() == 1 && p != -1) {
        x = min(x, mul[u] * a[u]);
        lcm *= mul[u] / gcd(mul[u], lcm);
        if (lcm > x) { ans = -1; return; }
    }
    ll num = 0;
    for (int i = 0, v; i < e[u].size(); ++i) {
        v = e[u][i];
        if (v == p) continue;
        num++;
    }
    for (int i = 0, v; i < e[u].size(); ++i) {
        v = e[u][i];
        if (v == p) continue;
        mul[v] = mul[u] * num;//子节点的倍数因子
        dfs(v, u);
    }
}


int main() {
    fast;
    int n; cin >> n;
    ll sum = 0; ans = 0; lcm = 1; x = inf;
    for (auto& i : e) i.clear();
    for (int i = 1; i <= n; ++i) { cin >> a[i]; sum += a[i]; }
    for (int i = 1, u = 0, v = 0; i < n; ++i) {
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1, -1);
    if (ans == -1) cout << sum << '\n'; else cout << sum - x + x % lcm << '\n';
    return 0;
}
