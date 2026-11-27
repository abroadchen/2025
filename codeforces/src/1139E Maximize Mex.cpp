//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
用链式前向星存储边：v 是邻接点，nxt 是下一条边指针，head[u] 是头指针。
额外多存了一个 t，用于后面按时间过滤（只有 t > T 的边才参与本轮匹配）
标准的匈牙利算法递归实现：

s[v]：右部点 v 当前匹配的左部点（-1 表示未匹配）。
vis[now]：用 now 做时间戳，避免每轮清空 vis 数组。
对每个相邻点，若它未访问且边的时刻满足 e[i].t > T，就用"增广路"思想尝试匹配
d[] 记录每个点被"激活/删除"的时刻，初始化为 inf。
d[rd()] = i：第 i 轮有一个点被标记，其时刻为 i
每个左部点 p[i] 连向右部点 c[i]，边权为时刻 d[i]
每一轮 T = i，把"时刻 ≤ i"的边排除（e[i].t > T 才走），即边随时间动态失效。
对左部点 0..w 依次尝试匈牙利匹配，若某个点 j 无法匹配，则输出 j 并结束本轮。
若全部点都能匹配，输出 w+1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1;i<=n;i++)
using namespace std;

constexpr int N = 5e3+5, inf = 1e9+7;

struct edge { int v, t, nxt; } e[N];

int head[N], cnt;
void add(int u, int v, int t) {
    e[++cnt] = {v,t,head[u]}; head[u] = cnt;
}

int now, vis[N], T, s[N];
bool dfs(int x) {
    for (int i = head[x]; i; i = e[i].nxt)
        if (e[i].t > T && vis[e[i].v] != now) {
            vis[e[i].v] = now;
            if (s[e[i].v] == -1 || dfs(s[e[i].v])) {
                s[e[i].v] = x; return 1;
            }
        }
    return 0;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, w, p[N], c[N], d[N], q;
int main() {
    fast;
    n = rd(), m = rd();
    rep(i,n) p[i] = rd(), w = max(w,p[i]);
    rep(i,n) c[i] = rd();
    q = rd();
    for (int i = 0; i <= n; i++) d[i] = inf;
    rep(i,q) d[rd()] = i;
    rep(i,n) add(p[i],c[i],d[i]);
    rep(i,q) {
        T = i;
        for (int j = 0; j <= m; j++) vis[j] = s[j] = -1;
        bool flg = 0;
        for (int j = 0; j <= w; j++) {
            now = j;
            if (!dfs(j)) {
                cout << j << '\n'; flg = 1;
                break;
            }
        }
        if (!flg) cout << w+1 << '\n';
    }
    return 0;
}