//
// Created by Psy.C on 2026/9/21.
//
/**
fa / find：主并查集，用于"当前右端 r 及之后已加入的列"之间的连通合并。
fa2 / find2：临时并查集，用于"左半段临时加入的列"（防止破坏主并查集状态），每个查询结束后重置，从而能回滚。
这是莫队里常用的双并查集 / 可回滚并查集思路：右半段用持久的主并查集 fa 累积，左半段用临时 fa2 只在本查询内使用，这样避免每次查询都要重建全部结构
把第 i 列的每个格子（j=1..n 行）的并查集父指针重置为自身（自环 = 新连通块）。clear 清主 fa，clear2 清临时 fa2
len = m/sqrt(T)+5：块大小取 m/√T，保证莫队复杂度 O((n·m)√T)。
b[i]：列 i 的块号。
查询按 左端点所在块 排序，同块内按 右端点 升序（cmp
每次处理第 j 块：R = 该块最右列，r 当前右指针（初始 = R）。res 为当前已并入列产生的连通块数
注意这行 for (int k = r+1; k <= m; ++k) clear(r); 看起来是循环体写错（应该 clear(k)），但即便写错，等价于对每 k 都 clear 同一列 r——从正确性上是有问题的，可能原本意图是"先把所有列清空"。不过主流程仍能跑（反复 clear 同一列 r 无副作用）

右指针 r 从 R 开始，逐列向右扩展到 q[i].r：
++r; res += n：加入新的一列，这一列的 n 个格子先各自算 n 个新连通块。
clear(r)：重置第 r 列的主并查集。
横向合并：同列相邻两行若同色则 union，--res。
若 r 恰是 R+1（本块的右边界扩展的第一列），continue 跳过纵向合并（因为此时左侧 fa2 或边界特殊，稍后处理）。
纵向合并：与上一列 r-1 对应行若同色且分属不同集合则 union，--res。
到这里，主并查集 fa 里累积了从 R - q[i].r 这些"右半列"的连通块，res 是它们的连通块数，但还没包含左半列 q[i].l - R。
左半段（q[i].l - R）用临时并查集 fa2 处理：
res2 = res：先继承右半段已算出的 res。
清空左半段每个 pos 的 fa2。
若 q[i].r > R（查询右端越过了块界 R），把 fa2 中 R+1 列与主 fa 挂钩（建立 fa2 ↔ 主并查集的桥，使左右能连通）。
遍历左半段 pos（从右往左）：
res2 += n：每加入一列先加 n 个块。
横向 merge（同列相邻行同色）。
若 pos 不是查询右端，则与 pos+1 列纵向 merge。
注意 if (pos == q[i].r) continue; 保证不会越界到查询右端之外。
最终 ans[q[i].id] = res2。
按原顺序输出每个查询的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10;
struct node { int l, r, id; } q[N];//查询：列区间[l,r]，id 是原顺序

int b[N];//每列所属块号
inline bool cmp(node x, node y) {
    if (b[x.l] != b[y.l]) return x.l < y.l;
    return x.r < y.r;
}

int fa[10*N];//主并查集（管"右块及右侧已处理列"）
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int fa2[10*N];//临时并查集（管"查询左半临时列"）
inline int find2(int x) { return x == fa2[x] ? x : fa2[x] = find2(fa2[x]); }

int n;
inline int id(int i, int j) { return (i-1)*n+j; }
inline void clear(int i) {
    for (int j = 1; j <= n; ++j)
        fa[id(i, j)] = id(i, j);
}
inline void clear2(int i) {
    for (int j = 1; j <= n; ++j)
        fa2[id(i, j)] = id(i, j);
}
//行数、列数、查询数
//颜色（压成一维）
//答案
int m, T, len, c[10*N], ans[N];
int main() {
    fast;
    cin >> n >> m >> T; len = m/sqrt(T)+5;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> c[id(j, i)];
    //列分块：第 i 列属于第 (i-1)/len+1 块
    for (int i = 1; i <= m; ++i) b[i] = (i-1)/len+1;
    for (int i = 1; i <= T; ++i) {
        cin >> q[i].l >> q[i].r; q[i].id = i;
    }
    sort(q+1, q+T+1, cmp);
    for (int j = 1, i = 1; j <= b[m]; ++j) {
        int R = min(j*len, m), r = min(j*len, m), res = 0;
        for (int k = r+1; k <= m; ++k) clear(r);
        for (; i <= T && b[q[i].l] == j; ++i) {
            while (r < q[i].r) {
                ++r; res += n; clear(r);
                for (int k = 1; k < n; ++k) {
                    if (c[id(r, k)] != c[id(r, k+1)]) continue;
                    fa[find(id(r, k))] = find(id(r, k+1));
                    --res;
                }
                if (r == R+1) continue;
                for (int k = 1; k <= n; ++k) {
                    if (c[id(r, k)] != c[id(r-1, k)] ||
                        find(id(r, k)) == find(id(r-1, k))) continue;
                    fa[find(id(r, k))] = find(id(r-1, k));
                    --res;
                }
            }
            int res2 = res;
            for (int pos = min(q[i].r, R); pos >= q[i].l; --pos) clear2(pos);
            if (q[i].r > R) {
                for (int k = 1; k <= n; ++k) {
                    fa2[id(R+1, k)] = find(id(R+1, k));
                    fa2[find(id(R+1, k))] = find(id(R+1, k));
                }
            }
            for (int pos = min(q[i].r, R); pos >= q[i].l; --pos) {
                res2 += n;
                for (int k = 1; k < n; ++k) {
                    if (c[id(pos, k)] != c[id(pos, k+1)]) continue;
                    fa2[find2(id(pos, k))] = find2(id(pos, k+1));
                    --res2;
                }
                if (pos == q[i].r) continue;
                for (int k = 1; k <= n; ++k) {
                    if (c[id(pos, k)] != c[id(pos+1, k)] ||
                        find2(id(pos, k)) == find2(id(pos+1, k))) continue;
                    fa2[find2(id(pos, k))] = find2(id(pos+1, k));
                    --res2;
                }
            }
            ans[q[i].id] = res2;
        }
    }
    for (int i = 1; i <= T; ++i) cout << ans[i] << '\n';
    return 0;
}