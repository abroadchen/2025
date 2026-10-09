//
// Created by Psy.C on 2026/10/9.
//
/**
e 存所有边，p 存查询中选出的边。
按 w（权值）排序、按 id 恢复原序两种比较。
fa 并查集 + 路径压缩 find
这是 Kruskal 求 MST 的模板，按权值从大到小/从小到大处理同权边：先把每组的端点压缩成它们当前所在连通块的代表元，再用并查集合并不成环的边。
处理完后按 id 恢复原顺序，供查询使用
每个查询：读入
K
K 条边的编号，取对应边放入 p。
按权值分组，对每一组权值：
先临时初始化涉及的端点（fa[x]=x），模拟"在所有更小权值的边已并入 MST 之后的并查集状态"（因为主程序已把端点压缩成代表元）。
再尝试把这些边加入 MST：若同权值区间内出现成环（u==v），说明这
K
K 条边不能同时出现在某个 MST 中，返回 false
读入查询数
q
q，逐个判断并输出 YES/NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5e2;
struct line { int u, v, w, id; } e[N], p[N];
bool operator<(const line& a, const line& b) { return a.w < b.w; }
bool cmp(const line& a, const line& b) { return a.id < b.id; }

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int K;
bool solve() {
    K = rd();
    for (int i = 1; i <= K; ++i) p[i] = e[rd()];//取出查询涉及的 K 条边
    sort(&p[1], &p[K+1]);//按权值分组
    for (int i = 1, j = 1; i <= K; i=j=j+1) {
        while (j < K && p[j+1].w == p[i].w) ++j;//同权区间 [i,j]
        for (int k = i; k <= j; ++k)
            fa[p[k].u] = p[k].u, fa[p[k].v] = p[k].v;//临时重建这些点的并查集
        for (int k = i; k <= j; ++k) {
            int u = find(p[k].u), v = find(p[k].v);
            if (u == v) return false;//同权内成环 → 不能同时入选
            fa[find(u)] = find(v);
        }
    }
    return true;
}

int main() {
    fast;
    int n = rd(), m = rd();
    for (int i = 1; i <= m; ++i)
        e[i].u = rd(), e[i].v = rd(), e[i].w = rd(), e[i].id = i;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    sort(&e[1], &e[m+1]);//按权值排序
    for (int i = 1, j = 1; i <= m; i=j=j+1) {
        while (j < m && e[j+1].w == e[i].w) ++j;//找到同权值的区间 [i,j]
        for (int k = i; k <= j; ++k)
            e[k].u = find(e[k].u), e[k].v = find(e[k].v);//压缩到当前连通块代表元
        for (int k = i; k <= j; ++k) {
            int u = find(e[k].u), v = find(e[k].v);
            if (u == v) continue;//成环则不能作为树边
            fa[find(u)] = find(v);//合并
        }
    }
    sort(&e[1], &e[m+1], cmp);//恢复原边序
    int q = rd();
    while (q--) cout << (solve()?"YES":"NO") << '\n';
    return 0;
}