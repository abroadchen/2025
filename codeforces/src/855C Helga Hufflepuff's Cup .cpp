//
// Created by Psy.C on 2026/9/30.
//
/**
m：总颜色数。
K：某一种特殊颜色的数量上限（或其中一个被指定的方面数量为 K）。
M：某类（特殊）点最多能出现多少个（背包容量上限），树形背包限制为 M
c=0/1/2：表示当前节点 x 被分到三种分类中的哪一种。
第二维 j：子树中"分类1"的节点总数，做树上背包，上限 M。
第三维 c：限制相邻两点的状态搭配
状态0：K-1 种；
状态1：只有 1 种（且计入背包计数）；
状态2：m-K 种
若 x 为状态 0，孩子可以是任意状态（0/1/2）→ 乘三者之和；
若 x 为状态 1，孩子只能是状态 0（状态1 不相邻同色）→ 只乘 f[to][k][0]；
若 x 为状态 2，孩子可以是状态 0 或 2（不能是 1）→ 乘 f[to][k][0]+f[to][k][2]。
j+k > M 提前 break 剪枝，保证状态1 总数不超过 M。这就是树上分组背包的合并过程，s[x] 记录当前孩子合并后的"状态1 背包大小上界"（截到 M
把根节点所有可能"状态1 个数 i"和根颜色状态 c 的方案数全部相加，即合法染色方案总数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

int tot, head[N], nxt[N<<1], to[N<<1];
inline void add(int x, int y) {
    nxt[++tot] = head[x]; head[x] = tot; to[tot] = y;
}

ll f[N][15][3], G[15][3];
int s[N], K, m, M;
inline void dfs(int x, int fa) {
    f[x][0][0] = K-1; s[x] = f[x][1][1] = 1; f[x][0][2] = m-K;
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] != fa) {
            dfs(to[i], x);
            memset(G, 0, sizeof(G));
            for (int j = 0; j <= s[x]; ++j)
                for (int k = 0; k <= s[to[i]]; ++k) {
                    if (j+k > M) break;
                    G[j+k][0] = (G[j+k][0]+f[x][j][0]*(f[to[i]][k][0]+f[to[i]][k][1]+f[to[i]][k][2]))%mod;
                    G[j+k][1] = (G[j+k][1]+f[x][j][1]*f[to[i]][k][0])%mod;
                    G[j+k][2] = (G[j+k][2]+f[x][j][2]*(f[to[i]][k][0]+f[to[i]][k][2]))%mod;
                }
            s[x] = min(s[x]+s[to[i]], M);
            for (int j = 0; j <= s[x]; ++j)
                for (int k = 0; k < 3; ++k) f[x][j][k] = G[j][k];
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

int n;
ll ans;
int main() {
    fast;
    n = rd(), m = rd();
    for (int i = 1, x, y; i < n; ++i)
        x = rd(), y = rd(), add(x, y), add(y, x);
    K = rd(), M = rd(); dfs(1, 0);
    for (int i = 0; i <= s[1]; ++i)
        for (int j = 0; j < 3; ++j)
            ans = (ans + f[1][i][j]) % mod;
    cout << ans;
    return 0;
}