//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
用链式前向星存无向树，add 一次加两条反向边
f[x]：在 x 的子树中，到根（x）距离最远的叶子节点（深度最深者）。
g[x]：次远的叶子（第二深）。
dep[x]：以当前根为基准，x 的深度。
对每个孩子维护 f[child]（孩子子树里最远的叶子），用它更新父亲的两个候选
用孩子的"最远叶子深度"更新父亲的最远/次远。

叶子判定 if (!cnt) f[x] = x;：叶子节点没有孩子，它自身就是"最远点"。

拼接最长路径 if (cnt >= 2)：

若 x 至少两个孩子，则可通过"孩子1的最远叶子 → x → 孩子2的最远叶子"拼一条路径。
路径长度 = dep[f[x]] + dep[g[x]] - 2*dep[x]（两个叶子的深度减去重复的根部分——即经过 x 的跨两个孩子的路径长度）。
记录全局最优 res 及转折点 pos = x。
info 的比较运算符 operator<：先比 x（这里是 dep[x]，即转折点深度），再比 y（路径长度）。用于选出最优的"分裂点"
第一次 dfs(1,0)：以 1 为根，找到"最优分裂点" pos（能让跨两条孩子路径最长的那条经过的点），并得到 A = f[pos]、C = g[pos]。此时 A、C 是 pos 的两棵不同子树里各自最远的叶子——即经过 pos 的最长路径的两个端点。
第二次 dfs(pos, 0)：换根到 pos，重新算每个节点深度与最远/次远叶子，得到 B = f[pos]、D = g[pos]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;

struct info {
    int x, y;
    bool operator<(const info &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
} res;

struct node { int a, b; } e[N<<1];

int k, head[N], nxt[N<<1];
void add(int a, int b) {
    e[++k] = {a,b}; nxt[k] = head[a]; head[a] = k;
    e[++k] = {b,a}; nxt[k] = head[b]; head[b] = k;
}

int f[N], g[N], dep[N], pos;
void dfs(int x, int fa) {
    int cnt = 0; f[x] = g[x] = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        if (e[i].b == fa) continue;
        cnt++; dep[e[i].b] = dep[x] + 1; dfs(e[i].b, x);
        //维护 x 子树内"深度最深"和"次深"的叶子
        if (dep[f[e[i].b]] > dep[f[x]]) g[x] = f[x], f[x] = f[e[i].b];
        else if (dep[f[e[i].b]] > dep[g[x]]) g[x] = f[e[i].b];
    }
    if (!cnt) f[x] = x;//叶子：它自己就是最远点
    if (cnt >= 2) {//至少两个孩子 → 可通过 x 的两条孩子路径"拼"出最长路径
        info tmp = {dep[x],dep[f[x]]+dep[g[x]]-dep[x]*2};
        if (res < tmp) res = tmp, pos = x;
    }
}

int n, A, B, C, D;
int main() {
    fast;
    cin >> n;
    for (int i = 1, a, b; i < n; i++) cin >> a >> b, add(a, b);
    dep[1] = 0; res = {0,0}; dfs(1,0); A = f[pos]; C = g[pos];
    dep[pos] = 0; res = {0,0}; dfs(pos,0); B = f[pos]; D = g[pos];
    cout << A << ' ' << B << '\n' << C << ' ' << D << '\n';
    return 0;
}