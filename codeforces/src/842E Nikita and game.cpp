//
// Created by Psy.C on 2026/9/27.
//
/**
标准倍增 LCA：f[u][i] 是 u 的 2^i 级祖先，dep[] 深度，k = log2(m)。
lca(x,y) 被重定义为两点间的距离（dep[x]+dep[y]-2*dep[lca]）——注意函数名虽叫 lca 但返回的是距离
初始：两个节点 u（父）和 u+1（子），直径端点存入 d1、d2，直径 d=1，输出 2（当前点数）。
每加一个叶子 n+1：
用 LCA 距离算它到 d1 端 和 d2 端 的距离 n1、n2。
若 n1 > d（比当前直径还大）：说明新节点让直径变长，它成为新的一端。原 d1 侧被淘汰，若原 d2 侧候选仍与新节点构成新直径则保留进 d1，然后新节点进 d2，d 更新。
对称处理 n2 > d。
若 n1 == d 或 n2 == d：新节点恰好与某端构成等长直径，把它追加到对应候选集合（不改变直径长度）。
输出 d1.size() + d2.size()：当前直径的所有可能端点数（题目要求统计这样的端点数）。
这里输出的不是直径长度，而是"能作为直径端点的节点个数"（d1 集合 + d2 集合的大小），因为 d1、d2 分别存了所有能作为左右端点的节点（多条等长直径的端点）。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

int f[N][21], dep[N], k;
void init(int u, int fa) {
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for (int i = 1; i <= k; ++i)
        f[u][i] = f[f[u][i-1]][i-1];
}

int get(int x, int y) {
    if (x == y) return x;
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = k; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
        if (x == y) return x;
    }
    for (int i = k; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int lca(int x, int y) { return dep[x] + dep[y] - 2*dep[get(x, y)]; }

int m, u, n(2), d(1);
vector<int> d1, d2;
int main() {
    fast;
    cin >> m >> u; k = log2(m); init(u+1, u);//初始连接：节点 u+1 挂到 u 下
    d1.push_back(u), d2.push_back(u+1);//第一对直径端点
    cout << 2 << '\n';//初始 2 节点，直径=1（两节点距离1）
    while (--m) {
        cin >> u; init(n+1, u);//新叶子 n+1 挂到 u 下
        //新节点 到 d1 任一候选的 距离  新节点 到 d2 任一候选的 距离
        int n1 = lca(n+1, d1[0]), n2 = lca(n+1, d2[0]);
        if (n1 > d) {//新节点与 d1 端距离 > 当前直径 d，扩大左端集合
            while (!d2.empty()) {
                if (lca(d2[d2.size()-1], n+1) == n1)
                    d1.push_back(d2[d2.size()-1]);
                d2.pop_back();
            }
            d2.push_back(n+1), d++;
        } else if (n2 > d) {//与 d2 端距离 > d，扩大右端集合
            while (!d1.empty()) {
                if (lca(d1[d1.size()-1], n+1) == n2)
                    d2.push_back(d1[d1.size()-1]);
                d1.pop_back();
            }
            d1.push_back(n+1), d++;
        }
        else if (n1 == d) d2.push_back(n+1);
        else if (n2 == d) d1.push_back(n+1);
        cout << d1.size()+d2.size() << '\n';
        n++;
    }
    return 0;
}