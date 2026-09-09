//
// Created by Psy.C on 2026/9/8.
//
/**
f[x]：x 的父节点（集合代表）。sz[x]：以 x 为根的集合大小（记录集合内顶点个数）。
init()：初始化每个点自成集合，大小 1。
find(x)：找 x 所在集合代表，带回路径压缩。
uni(x,y)：把 x、y 所在集合合并（若已在同一集合则忽略），同时把 sz 累加（维护集合顶点数）
e[]：存储所有边（以便稍后再遍历统计）。
读入 n（顶点数）、m（边数）。
第一遍遍历所有边，把它们读入 e[] 并同时 uni 合并两个端点——这样所有连通的顶点会归入同一个集合
第二遍遍历所有边，用 cnt[find(e[i].u)]++ 统计每个连通分量（根代表）‍内部的边数。
find(e[i].u) 是边两端所在集合的根（此时两点在同一集合），把这条边计入该连通分量的边数
对每个集合代表 i（i==find(i) 表示 i 是自己所在连通分量的根）：
该连通分量若有 sz[i] 个顶点，那么它若是一个完全图（团）‍，内部应有的边数是组合数 sz[i]*(sz[i]-1)/2（C(sz,2)）。
若实际的边数 cnt[i] 不等于这个完全图的边数，则不是合法结构，输出 "NO" 并结束。
用 (long long) 防止乘法溢出。
若所有连通分量都满足"内部边数 = 完全图应有边数"，则输出 "YES"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1.5e5+5;

struct Edge { int u, v; } e[N];

int n, f[N], sz[N];
void init() {
    for (int i = 1; i <= n; ++i)
        f[i] = i, sz[i] = 1;
}

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void uni(int x, int y) {
    int a = find(x), b = find(y);
    if (a != b) {
        f[b] = a;
        sz[a] += sz[b];
    }
}

int m, cnt[N];
int main() {
    fast;
    cin >> n >> m; init();
    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v;
        uni(e[i].u, e[i].v);
    }
    for (int i = 0; i < m; ++i) cnt[find(e[i].u)]++;
    for (int i = 1; i <= n; ++i)
        if (i == find(i)) {
            if ((long long)sz[i]*(sz[i]-1)/2 != cnt[i]) {
                cout << "NO\n"; return 0;
            }
        }
    cout << "YES\n";
    return 0;
}