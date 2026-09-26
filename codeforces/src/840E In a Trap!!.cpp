//
// Created by Psy.C on 2026/9/26.
//
/**
邻接表存树（无向，双向加边）。
num[] 存边，head[] 是每条链的头
从根（1）DFS，记录每个点的 父节点 fa[] 和 深度 dep[]（根为 0）。
树上路径查询的基础：u 往根爬时用 fa[]，深度决定路径长度。
注意：这里路径处理是从 v 向上爬到 u（后面查询里 v 向上走

P = 260：块大小（分块步长）。
M = 5e3：Trie 节点数上限。
f[N][P]：f[x][b] = 从点 x 向上走「恰好 b 步」这一段（即约 b+1 个节点：x、fa[x]…）中，步数异或该点权值的最大值（预计算）。
jp[N]：跳表，jp[x] = 从 x 向上跳约 P-4（256）步到达的祖先，用于快速跨越一整块
第一循环：建 Trie。 从 i 开始向上走 256 步，第 j 步的点是 i, fa[i], fa[fa[i]]…（即 x），把 t = a[x] ^ j（当前点权值异或上它在块内的步数 j）插入一个 17 位二进制 Trie。所有点一起插入，Trie 节点互享（sc 累积）。

第二循环：贪心最大异或。 对每个 j（0-255），构造 t = j<<8，然后在 Trie 中做最大异或贪心（每高位优先走与当前位相反的 c^1 分支），得到 sum，存入 f[i][j] = sum。

这里 j<<8 的 8 位是"块内位置"的高位部分，配合 Trie 里存的 a[x]^j。这样 f[i][j] 就能回答"从 i 点向上的整块中，某一步（模 256）j 所对应的最大异或值"。
关键在于利用了 (x ^ j) 中 j 只有 8 位（0-255）‍，而 Trie 存的是 a[x]^j（17 位，因为 a 值域加上 j）。
jp[i]：记下这 256 步跳到的祖先 x（即块顶的上一格），用于整块跳跃。

深度不足的点不预处理（if (dep[i] >= P-5)），因为从它往上不够一整块。
对于每次查询 (u, v)（这里假设 dep[v] >= dep[u]，即 v 更深，从 v 向上爬到 u）：

第一步：整块跳跃。 只要 v 距 u 还够一整块（dep[v]-dep[u] >= P-5 ≈ 255），就用预计算的块：ans = max(ans, f[v][base]) 一次跳过 256 步，然后 v = jp[v]，base++（base 是全局步数序号，随整块累加）。这一步把长路径压成 O(len/256) 次。

第二步：末尾逐点。 剩余不足一整块的部分，base = base*(P-4)（还原成真实步数基数），然后 v 一步一步 fa[v] 向上爬，每一步 ans = max(ans, a[v]^base)，base++。一直爬到 u 的父节点 fa[u]（因为 u 自身也要算，循环条件 v != fa[u] 会在 v 到 u 时停，但 u 被跳过？——实际循环结束时 v 停在 fa[u]，u 本身未被算入最后一步，这是边界处理）。

注意：这里的 base 每次查询都从 0 开始，表示"从 v 走向 u 的路径上第 base 步"，正好对应预处理时的步数序号 j，从而能复用 f[v][base] 与 Trie 的 j<<8 设计。
最终对每次询问输出路径上 a[点]^(该点距 v 的步数) 的最大值 ans。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e4+5, M = 5e3, P = 260;

struct node { int to, nxt; } num[N<<1];

int cnt, head[N];
void add(int x, int y) {
    num[++cnt].to = y; num[cnt].nxt = head[x]; head[x] = cnt;
}

int fa[N], dep[N];
void dfs(int x) {
    for (int i = head[x]; i; i = num[i].nxt) {
        if (num[i].to != fa[x]) {
            dep[num[i].to] = dep[x] + 1;
            fa[num[i].to] = x;
            dfs(num[i].to);
        }
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, q, a[N], sc, son[M][2], f[N][P], jp[N], u, v, ans, base;
int main() {
    fast;
    n = rd(), q = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    for (int i = 1; i < n; ++i) u = rd(), v = rd(), add(u, v), add(v, u);
    dfs(1);
    for (int i = 1, t, now, c, sum; i <= n; ++i) {
        if (dep[i] >= P-5) {
            int x = i; sc = 0; son[0][0] = son[0][1] = 0;
            for (int j = 0; j < P-4; ++j, x = fa[x]) {
                t = a[x]^j; now = 0;
                for (int k = 16; k >= 0; --k) {
                    c = (t>>k) & 1;
                    if (!son[now][c]) son[now][c] = ++sc, son[sc][0] = son[sc][1] = 0;
                    now = son[now][c];
                }
            }
            for (int j = 0; j < P-4; ++j) {
                t = j<<8; now = sum = 0;
                for (int k = 16; k >= 0; --k) {
                    c = (t>>k) & 1;
                    if (son[now][c^1]) now = son[now][c^1], sum += 1<<k;
                    else now = son[now][c];
                }
                f[i][j] = sum;
            }
            jp[i] = x;
        }
    }
    while (q--) {
        u = rd(), v = rd(); ans = base = 0;
        for (; dep[v] - dep[u] >= P-5; v = jp[v])
            ans = max(ans, f[v][base]), base++;
        for (base=base*(P-4); v != fa[u]; v = fa[v], ++base)
            ans = max(ans, a[v]^base);
        cout << ans << '\n';
    }
    return 0;
}