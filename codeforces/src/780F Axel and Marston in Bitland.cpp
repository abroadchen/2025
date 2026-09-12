//
// Created by Psy.C on 2026/9/12.
//
/**
f[p][s][x] 是一个 bitset：从点 x、状态 p，恰好走 2^s 步，到达的节点集合。
初态：f[t][0][x][y]=1 表示一步（2^0）内，x→y 若边权为 t 则可达。
这里的 p（0/1）是交替状态：乘法中的一条规则是——走第 2^s 段的起段性与上段交替（即"路径的奇偶/颜色"），f[p][s][x] 表示从"颜色段 p"开始的连续 2^s 步
经典倍增：从 x 走 2^s 步 = 先走 2^(s-1) 步到 k，再走 2^(s-1) 步。
关键：第二段的状态变号 p^1（交替奇偶），因为走了 2^(s-1) 步会翻转当前状态
若从 1 出发用状态 0 走 2^60 步还能到达（包括回到能继续的环），说明路径可以无限延伸 → 输出 -1
从高位到低位贪心（二进制拼接最大可行步数）。
pre 记录当前可达节点集合；now 是当前所处状态。
对每个二进制位 s，尝试从当前可达集再走 2^s 步（保持状态 now），若还能到某些点（t.count()>0），则把 ans 加上 2^s，更新可达集与状态。
ans 超过 1e18 判无穷 → -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 505, M = 65;
constexpr ll inf = 1e18;
bitset<N> f[2][M][N], pre, t;
ll ans;
int main() {
    fast;
    int n = rd(), m = rd();
    while (m--) {
        int x = rd(), y = rd(), t = rd();
        f[t][0][x][y] = 1;
    }
    for (int s = 1; s <= 60; ++s)
        for (int p = 0; p <= 1; ++p)
            for (int x = 1; x <= n; ++x)
                for (int k = 1; k <= n; ++k)
                    if (f[p][s-1][x][k]) f[p][s][x] |= f[p^1][s-1][k];
    for (int i = 1; i <= n; ++i)
        if (f[0][M-5][1][i]) {
            cout << "-1\n"; return 0;
        }
    int now(0); pre[1] = 1;
    for (int s = M-6; s >= 0; --s) {
        t.reset();
        for (int i = 1; i <= n; ++i)
            if (pre[i]) t |= f[now][s][i];
        if (t.count()) {
            pre = t; now ^= 1; ans += 1ll<<s;
            if (ans > inf) {
                cout << "-1\n"; return 0;
            }
        }
    }
    cout << ans;
    return 0;
}