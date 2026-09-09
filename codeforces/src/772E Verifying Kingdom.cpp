//
// Created by Psy.C on 2026/9/9.
//
/**
邻接存储：每个点 u 有三个槽 e[u][0..2]（0 是父，1、2 是两个儿子）。这是一棵三叉有根树（每个节点可有 0 或 2 个子节点——其实是"二叉树"但用 0..2 存三个连接：父 + 两个子）。
add(u,x,v)：给 u 的第 x 槽连向 v，并设 v 的第 0 槽为 u（记录父）。
节点结构：e[n][0]=parent，e[n][1]、e[n][2] 是两个 child
dfs(u,pre)：统计以 u 为根（不含 pre 方向、不含已被标记 vis 的点）的连通块大小。返回节点个数。用于后续找子树大小/重心
dfs2 在大小为 ts 的子树里找重心：
对每个孩子计算 sz，mx[u] = 所有孩子子树的最大大小，再与上方剩余部分 ts-sz[u] 取最大（这是"去掉 u 后最大连通块"）。
若该最大连通块 ≤ ts/2，且 u 有孩子（e[u][1] 非空即至少有一个 child），则 u 是重心，更新全局 rt。
作用是：对当前待分裂的树块找重心，让分治尽可能均衡（每次连到子树大小减半
读入 n 后，lf 是当前要新插入的叶子节点编号。
若当前 u 是叶子（!e[u][1]，没有孩子）：把它挂到父节点 f 的对应槽（sn 判断 u 是第 1 还是第 2 个孩子），新建一个节点 tot+1 作为中间节点，把 u 和 lf 作为它的两个叶子挂上。sym[tot] 记录这两个叶子代表（用于之后判断方向的锚点）
找当前子树 u 的重心 rt，标记 vis 已访问（分治拆分子树）。
发起交互询问：输出三个数 sym[u][0] sym[u][1] lf（即"把 lf 与这两个叶子放一起判断位置"），fflush 强制刷新。
读回结果 t（X/Y/Z 字符串）：
'X' → nxt = 0（表示往父方向/左边走）
'Y' → nxt = 2
'Z' → nxt = 1
这是依据"三个节点两两距离"判断新叶 lf 落在哪一侧：具体是判断这三者构成的树的形态（哪两个属于同一子树），从而决定向哪个方向继续二分
依据 nxt 决定下探方向：若目标方向有未访问的节点，就递归 dfs3 继续二分。
若目标方向已到头（或为空）：
nxt=0 且 v 为空：直接把 lf 挂到 u 上做成新根 root。
nxt=0 且 v 存在：把 u 和 lf 作为 v 的孩子挂进去。
nxt=1/2：当前 u 空缺的那个孩子槽填上 lf，sym 记录代表。
本质是向根方向或子树方向动态插入叶子，并把 sym（叶子代表）随之更新
读入 n。初始建树根 root=n+1，两个叶子 1 和 2。
循环插入叶子 3..n：每轮清空 vis，从 root 开始 dfs3 交互式定位并插入。
全部插完后输出 -1（表示交互询问结束），随后输出整棵树的每个节点的父节点（e[i][0]），无父则 -1
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e3+5;

int e[N][3];
void add(int u, int x, int v) {
    e[u][x] = v, e[v][0] = u;
}

int vis[N];
int dfs(int u, int pre) {
    int res = 1;
    for (int i = 0; i <= 2; ++i) {
        if (!e[u][i] || e[u][i] == pre || vis[e[u][i]]) continue;
        res += dfs(e[u][i], u);
    }
    return res;
}

int sz[N], mx[N], rt;
void dfs2(int u, int pre, int ts) {
    sz[u] = 1, mx[u] = 0;
    for (int i = 0; i <= 2; ++i) {
        if (!e[u][i] || e[u][i] == pre || vis[e[u][i]]) continue;
        dfs2(e[u][i], u, ts);
        mx[u] = max(mx[u], sz[e[u][i]]);
        sz[u] += sz[e[u][i]];
    }
    mx[u] = max(mx[u], ts-sz[u]);
    if (e[u][1] && mx[u] <= ts/2) rt = u;
}

int tot, sym[N][2], root;
void dfs3(int u, int lf) {
    if (!e[u][1]) {
        int f = e[u][0], sn;
        if (e[f][1] == u) sn = 1; else sn = 2;
        add(f, sn, ++tot); add(tot, 1, u); add(tot, 2, lf);
        sym[tot][0] = u, sym[tot][1] = lf;
        return;
    }
    rt = 0;
    int s = dfs(u, 0); dfs2(u, 0, s);
    u = rt;
    vis[u] = 1;
    printf("%d %d %d\n", sym[u][0], sym[u][1], lf); fflush(stdout);
    int nxt; char t[10]; scanf("%s", t);
    if (t[0] == 'X') nxt = 0;
    else if (t[0] == 'Y') nxt = 2;
    else nxt = 1;
    if (e[u][nxt] && !vis[e[u][nxt]]) dfs3(e[u][nxt], lf);
    else {
        int v = e[u][nxt];
        if (nxt == 0) {
            if (!v) {
                add(++tot, 1, u); add(tot, 2, lf);
                sym[tot][0] = sym[u][0], sym[tot][1] = lf;
                root = tot;
                return;
            }
            int sn = e[v][1] == u ? 1 : 2;
            add(v, sn, ++tot); add(tot, 1, u); add(tot, 2, lf);
            sym[tot][0] = sym[u][0], sym[tot][1] = lf;
        } else {
            add(u, nxt, ++tot); add(tot, 1, v); add(tot, 2, lf);
            if (!e[v][1]) sym[tot][0] = v;
            else sym[tot][0] = sym[v][0];
            sym[tot][1] = lf;
        }
    }
}


int main() {
    int n; scanf("%d", &n);
    root = tot = n+1;
    add(root, 1, 1); add(root, 2, 2);
    sym[n+1][0] = 1, sym[n+1][1] = 2;
    for (int i = 3; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        dfs3(root, i);
    }
    puts("-1");
    for (int i = 1; i <= tot; ++i)
        printf("%d ", e[i][0] ? e[i][0] : -1);
    return 0;
}