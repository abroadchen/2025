//
// Created by Psy.C on 2026/9/24.
//
/**
标准链式前向星存无向图（每条边加两次）。
du[x] 记录点 x 的度数（加边次数）
fa[N]：DFS 父节点。
ans[N]：最终给每个点分配的分数。
X：当前 DFS 连通块中找到的"三叉节点"候选。
vis：访问标记；ok：已找到可行构造；v2：标记环上/路径上的点。
DFS 从每个未访问点开始，尝试找出可行构造：

发现环：把环上每个点分数记为 1，ok=1 立即返回。
度>3 的节点 x：把 x 的所有邻居分数设为 1，x 本身设为 2，判定可行。
度=3 的三叉节点：
若是第一个三叉节点，记录到 X，继续搜。
若之前已有 X（出现第二个三叉节点）：构造一条"环路径"，把 x 与 X 之间路径上的点标 2，x、X 各自的邻居标 1，判定可行。
这本质上是图里有环 → 一组构造；有两个三叉节点 → 另一组构造。
calc：计算以 x 为根的子树大小 sz[x]（不含 x 自身）。
get：沿树向下分配分数：ans[x] = ans[f]/(sz[x]+1) * sz[x]。
含义：父分数的分配需按子树的规模比例切分，要求 ans[f] 能被 sz[x]+1 整除。
若父分数为 0，子分数也为 0
主循环遍历每个连通块（未访问点）：

每个连通块跑一次 dfs，尝试上面的环/双三叉/度>3 构造，成功则 break。
若 dfs 只找到一个三叉节点且没触发 ok，就进入三叉节点的分数分配：
用 calc 算 X 三棵子树大小。
按子树大小排序 id[0] ≤ id[1] ≤ id[2]。
设 xx, yy, zz = 三棵子树大小+1（X 的"权"后缀和）。
约束检查：xx·yy + yy·zz + xx·zz ≤ xx·yy·zz 才可行（否则跳过，判定 NO）。
按大小分档给 ans[X] 设 3 或 4（并在 get 中继续分配），否则 ans[X] = xx*yy*zz。
对三棵子树跑 get 完成向下分配，ok=1
若在某连通块找到构造 → 输出 YES 和每个点的分数。
否则 NO
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+5;
struct edge { int to, nxt; } e[N<<1];
int cnt, head[N], du[N];
void add(int x, int y) {
    e[++cnt].nxt = head[x], head[x] = cnt, e[cnt].to = y;
    du[x]++;
}
int fa[N], ans[N], X;
bool vis[N], ok, v2[N];
void dfs(int x, int f) {
    fa[x] = f; vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != f) {
            if (vis[e[i].to]) {
                ok = 1;//发现环
                for (; 1; x = fa[x]) {
                    ans[x] = 1;//环上每个点分数=1
                    if (x == e[i].to) break;
                }
                return;
            }
            dfs(e[i].to, x);
            if (ok) return;
        }
    }
    if (du[x] > 3) {
        for (int i = head[x]; i; i = e[i].nxt) ans[e[i].to] = 1;
        ans[x] = 2; ok = 1;
        return;
    }
    if (du[x] == 3) {
        if (X) {//已有另一个三叉节点 → 扯环路径
            for (int i = head[x]; i; i = e[i].nxt) ans[e[i].to] = 1;
            for (int i = head[X]; i; i = e[i].nxt) ans[e[i].to] = 1;
            int y = x;
            for (; x; x = fa[x]) v2[x] = 1;
            for (; X; X = fa[X]) {
                ans[X] = 2;
                if (v2[X]) break;
            }
            for (; y != X; y = fa[y]) ans[y] = 2;
            ok = 1;
            return;
        }
        X = x;//记录第一个三叉节点
    }
}

int sz[N];
void calc(int x, int f) {
    sz[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != f) {
            calc(e[i].to, x);
            sz[x] += sz[e[i].to];
        }
    }
}
void get(int x, int f) {
    if (!ans[f]) ans[x] = 0;
    else ans[x] = ans[f]/(sz[x]+1)*sz[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != f) {
            sz[e[i].to] = sz[x] - 1;
            get(e[i].to, x);
        }
    }
}

int t, n, m, id[3];
int main() {
    for (scanf("%d", &t); t--; ) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) head[i] = ans[i] = sz[i] = du[i] = 0;
        for (int i = 1; i <= n; ++i) vis[i] = v2[i] = 0;
        cnt = ok = 0;
        for (int x, y; m--; ) {
            scanf("%d%d", &x, &y);
            add(x, y); add(y, x);
        }
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                X = 0; dfs(i, 0);
                if (ok) break;
                if (!X) continue;
                for (int j = head[X], k = 0; j; j = e[j].nxt, ++k) {
                    calc(e[j].to, X); id[k] = e[j].to;
                }
                for (int j = 0; j < 3; ++j)
                    for (int k = j+1; k < 3; ++k)
                        if (sz[id[j]] > sz[id[k]]) swap(id[j], id[k]);
                int xx = sz[id[0]]+1, yy = sz[id[1]]+1, zz = sz[id[2]]+1;
                if (1ll*xx*yy+1ll*yy*zz+1ll*xx*zz > 1ll*xx*yy*zz) continue;
                if (xx >= 3) ans[X] = 3, sz[id[0]]=sz[id[1]]=sz[id[2]] = 2;
                else if (yy >= 4) ans[X] = 4, sz[id[1]]=sz[id[2]] = 3;
                else ans[X] = xx*yy*zz;
                for (int j : id) get(j, X);
                ok = 1;
                break;
            }
        }
        if (ok) {
            puts("YES");
            for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
            puts("");
        } else puts("NO");
    }
    return 0;
}