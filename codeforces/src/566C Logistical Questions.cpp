//
// Created by Psy.C on 2026/3/12.
//
/**
读入节点数n和每个节点的权值a[i]
重心查找函数: 找到树的重心
siz[u]: 以u为根的子树大小
cur[u]: u节点的最大子树大小
重心定义：使得最大子树最小的节点

距离累加函数: 计算从某点出发到所有点的加权距离
s1: 主要代价函数，包含 a[u] * dis * sqrt(dis) 项
s2: 辅助代价函数
dp[top]: 以top为起点的代价

主解决函数: 使用分治策略寻找最优节点
遍历当前节点的所有子树
如果某个子树的代价为负，说明该子树中可能存在更优解
递归处理该子树

找到初始重心
从重心开始分治求解
输出最优节点（+1转换为1基索引）和最小代价

树分治：O(n log n)
每次递归处理：O(n)
总体：O(n log n)
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ll long long
using namespace std;
constexpr double inf = 1e20;

template<class T>
bool maxx(T& a, const T& b) {
    if (a < b) { a = b; return true; }
    return false;
}

int n;
int main() {
    fast;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<ii>> g(n);
    for (int i = 0, u, v, w; i < n-1; ++i) {
        cin >> u >> v >> w; u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<int> siz(n), cur(n), vis(n);
    int rt = -1;
    function<void(int,int,int)> find = [&](int u, int fa, int sum) {
        siz[u] = 1, cur[u] = 0;
        for (const auto v: g[u] | views::keys) {
            if (v == fa || vis[v]) continue;
            find(v, u, sum);
            siz[u] += siz[v];
            maxx(cur[u], siz[v]);
        }
        maxx(cur[u], sum - siz[u]);
        if (rt == -1 || cur[u] < cur[rt]) rt = u;
    };
    double s1, s2;
    vector<double> dp(n);
    function<void(int,int,int,ll)> get = [&](int u, int fa, int top, ll dis) {
        s1 += a[u] * dis * sqrtl(dis);
        s2 += a[u] * sqrtl(dis) * 3 / 2;
        dp[top] += a[u] * sqrtl(dis) * 3 / 2;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            get(v, u, top, dis + w);
        }
    };
    pair res{-1, inf};
    auto solve = [&](auto&& self, int u) {
        if (vis[u]) return;
        vis[u] = 1;
        s1 = s2 = 0;
        for (auto [v, w] : g[u]) {
            dp[v] = 0;
            get(v, u, v, w);
        }
        if (s1 < res.second) res = {u, s1};
        for (const auto v: g[u] | views::keys) {
            if (s2 - dp[v] * 2 < 0) {
                rt = -1;
                find(v, u, siz[v]);
                self(self, rt);
                break;
            }
        }
    };
    find(0, -1, n);
    solve(solve, rt);
    printf("%d %.10lf\n", res.first + 1, res.second);
    return 0;
}