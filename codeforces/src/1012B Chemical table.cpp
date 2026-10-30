//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
find(x)：查找 x 所在集合的根，带路径压缩（递归时把路径上节点直接指向根），用于加速。
简写：x == fa[x] ? x : fa[x] = find(fa[x]) ——若不是根就递归找父并更新
merge(x, y)：合并 x 和 y 所在集合。
若已在同一集合返回 0（合并无效），否则把 x 的根指向 y 的根返回 1（说明成功减少了 1 个连通块）
把节点 1..n 视为"行"（r），节点 n+1..n+m 视为"列"（c）。fa[i] = i 各自成集
初始答案设为 n + m - 1。
含义：若没有任何边，需要 n+m 个连通块，把它们连成一个整体至少需要 n+m-1 条边（树的性质：n 个节点连成树需 n-1 条边）
循环处理 q 次询问：每次读入一个格子/关系 (r, c)。
merge(r, c+n)：把行 r 和列 c（节点编号 c+n，偏移 n 以避免和行冲突）合并。
若这次合并成功减少了一个连通块（merge 返回 1），ans 就减 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 4e5+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int merge(int x, int y) {
    if (find(x) == find(y)) return 0;
    fa[find(x)] = find(y);
    return 1;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


int main() {
    fast;
    int n = rd(), m = rd(), q = rd();
    for (int i = 1; i <= n+m; i++) fa[i] = i;
    int ans = n + m - 1;
    while (q--) {
        int r = rd(), c = rd();
        ans -= merge(r, c+n);
    }
    cout << ans << '\n';
    return 0;
}