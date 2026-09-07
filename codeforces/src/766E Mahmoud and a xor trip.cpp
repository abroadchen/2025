//
// Created by Psy.C on 2026/9/7.
//
/**
to[]：边的终点。
nxt[]：下一条边（同一起点的）下标。
head[u]：u 的第一条边下标。
idx：边计数

f[N][2]：f[u][0/1] 表示以 u 为根的子树中，经过/属于 u 的颜色为 0 或 1 的节点数（用于路径计数）。
col[N]：当前位每个节点的颜色（0/1）。
ans：全局答案（累加各 bit 的贡献）。
now：当前位权重（1,2,4,...），当前处理的是二进制的哪一位。
参数说明：dfs(u, fa, s) —— s 是从根到 u 路径上当前累计的异或值（进入时由父节点传下来）。

f[u][s]=1, f[u][s^1]=0：初始化——u 自身的"当前异或状态"为 s 时计数 1，相反状态为 0。

遍历所有儿子 v：

递归深度优先：dfs(v, u, s ^ col[v]) —— 累计异或值 s 再异或上 v 的颜色 col[v]（因为路径异或需要累加）。
统计贡献：
若 col[u] == 1：当 u 和儿子同色时，路径段有贡献。ans += (f[u][0]*f[v][0] + f[u][1]*f[v][1]) * now —— u 状态 0×v 状态 0，加上状态 1×状态 1（同色组合数），乘上当前位权重 now。
若 col[u] == 0：当 u 和儿子异色时才有贡献。ans += (f[u][1]*f[v][0] + f[u][0]*f[v][1]) * now —— 状态 1×状态 0 和 0×1（异色组合数）。
合并：f[u][0] += f[v][0]; f[u][1] += f[v][1] —— 把儿子子树计数并入 u。

初始化 head 为 -1，读入 n。

读入 n 个点权 w[i]，先把每个点权直接加到 ans（每个点自身也计入总贡献，作为路径长度为 0 的部分）。

读入 n-1 条边建树（无向，双向 add）。

按位处理循环（0-21，共 22 位）
每次迭代取每个点权的最低位当作该点的颜色（0/1），然后右移整个数组准备下一位。
对这位调用树 DP dfs(1,0,col[1])，累加该位贡献进 ans。
每轮把权重 now 左移一位（×2）。
循环 22 次（i=0..21），处理到 2^21 位，保证能覆盖 long long 值的所有相关位（点权范围）。
最后输出 ans。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5;

int to[N<<1], nxt[N<<1], head[N], idx;
void add(int u, int v) {
    to[idx] = v, nxt[idx] = head[u], head[u] = idx++;
}

int f[N][2], col[N], ans, now=1;
void dfs(int u, int fa, int s) {
    f[u][s] = 1, f[u][s^1] = 0;
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u, s^col[v]);
        if (col[u]) ans += (f[u][0]*f[v][0]+f[u][1]*f[v][1])*now;
        else ans += (f[u][1]*f[v][0]+f[u][0]*f[v][1])*now;
        f[u][0] += f[v][0]; f[u][1] += f[v][1];
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, w[N];
signed main() {
    fast;
    memset(head, -1, sizeof(head)); n = rd();
    for (int i = 1; i <= n; ++i) w[i] = rd(), ans += w[i];
    for (int i = 1; i <= n-1; ++i) {
        int u = rd(), v = rd();
        add(u, v); add(v, u);
    }
    for (int i = 0; i <= 21; ++i) {
        for (int j = 1; j <= n; ++j) {
            col[j] = w[j]&1;
            w[j] >>= 1;
        }
        dfs(1, 0, col[1]);
        now <<= 1;
    }
    cout << ans << '\n';
    return 0;
}