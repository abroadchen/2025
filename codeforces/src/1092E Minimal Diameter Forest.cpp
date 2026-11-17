//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
d[x]：DFS 中 x 的深度（距起点的距离）。
mx：当前找到的最远深度。
k：最远深度的点（直径一端）。
fa[x]：x 的父节点（记录路径）。
vis[x]：标记是否已访问。
v[x]：邻接表。
从 x 出发 DFS，f 是父节点。
若 d[x] > mx 则更新全局最远点 k 和最远深度 mx。
记录 fa[x]、标记 vis，递归访问孩子（跳过父亲防回头），孩子深度 = 父深度+1。
作用：两次调用即可求树的直径与直径路径（第一次任取起点找最远点 k，第二次从 k 找另一端）
读 n 点、m 边，建无向图邻接表
遍历每个未访问点 i：说明发现一个新连通块（树）‍；
第一次 dfs(i,0)：从任意点出发，找到最远点 k（直径一端），最远深度 mx。
第二次 dfs(k,0)：从 k 再出发，找到直径另一端，记 mx 为该树直径长度，fa[] 记录了从 k 到另一端这颗直径的父链
沿 fa 向上走 mx/2 步，找到直径的中点 k（图论中的"树中心点"，作为这棵树归并用的连接点）
z 维护所有树中最大直径长度，kk 记录直径最大的那棵树的中心点
ans[k] = (mx+1)/2：这棵树中心点对外的"贡献半径" = 直径长度向上取整的一半（即该树中心到树内最远叶子的距离上限）。
vv.push_back(k)：记录每棵树的中心点
对所有中心点 x：
若 x 不是最大树中心 kk，ans[x]++：因为把 x 接到 kk 上会增加 1 条边的距离（连边贡献）。
维护两棵最大的 ans 值 m1、m2
最终最小半径 = max(最大树的直径 z, 两棵最大中心贡献之和 m1+m2)。
因为最坏情况下，最远距离取决于"最大树内部直径"与"跨接到 kk 后两棵最深的树的拼接距离"中的较大者
输出连边方案：把所有非 kk 的中心点连到 kk 上（共 vv.size() - 1 条边）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+10;

int d[N], mx, k, fa[N], vis[N];
vector<int> v[N];
void dfs(int x, int f) {
    if (d[x] > mx) { mx = d[x]; k = x; }
    fa[x] = f; vis[x] = 1;
    for (auto y : v[x]) {
        if (y == f) continue;
        d[y] = d[x] + 1;
        dfs(y, x);
    }
}

int n, m, x, y, z = -1, kk, ans[N];
vector<int> vv;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) { cin >> x >> y; v[x].push_back(y); v[y].push_back(x); }
    rep(i,n) if (!vis[i]) {
        mx = -1; d[i] = 0; dfs(i,0);
        mx = -1; d[k] = 0; dfs(k,0);
        rep(j,mx/2) k = fa[k];
        if (z < mx) z = mx, kk = k;
        ans[k] = (mx+1)/2; vv.push_back(k);
    }
    int m1 = 0, m2 = 0;
    for (auto x : vv) {
        if (x != kk) ans[x]++;
        if (ans[x] > m1) m2 = m1, m1 = ans[x];
        else if (ans[x] > m2) m2 = ans[x];
    }
    cout << max(z, m1+m2) << '\n';
    for (auto x : vv) if (x != kk) cout << x << ' ' << kk << '\n';
    return 0;
}