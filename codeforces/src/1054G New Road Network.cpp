//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
b[j]：点 j 的"集合位图"。b[j].set(i) 表示点 j 属于集合 i。两个点的 b 做按位与，就能 O(1) 数出它们共同属于多少个集合。
dis[i]：Prim 算法中，点 i 距当前已加入 MST 集合的"最大共享集合数"（即候选边权）。
p[i]：Prim 的父节点，用来记录生成树的边。
eu/ev：输出用的两端点数组。
ec：已记录的树边计数。
vis[i]：Prim 中该点是否已加入 MST。
ans：所有集合累加的"保底可用边数"。
tot：MST 的总权。
s：读入每行串的缓冲区。
重置每个点的 bitset、访问标记，dis 初始 -1（表示不可达），边数计数清零，ans 清零
对每个包含超过 1 个点的集合，ans += cnt - 1。
含义：一个集合内有 cnt 个点，若要让这 cnt 个点由该集合的覆盖连接紧密，最理想它能"保住" cnt-1 条边（构成一棵小树）。把所有集合的 cnt-1 累加，就是"理论上总共能搭出的最大边权上限"。
ans 就是后续判断可行性的期望总边权
这是一个最大生成树（Maximum Spanning Tree）‍的 Prim 实现，边权 = 两点的共享集合数 (b[j]&b[u]).count()。
外层 n 轮，每轮在未访问点中挑 dis 最大者 u 加入集合；tot += dis[u] 累加总权；记录树边；然后更新其它未访问点的 dis 和父指针 p。
本质上：尽量最大化"所有树边被集合共同覆盖"的总量。
两个必要条件：
ec == n-1：生成树恰好有 n-1 条边（连通完整）。
tot == ans：最大生成树的总权恰好等于所有集合累加的"理想最大边权上限"。
两点都满足 → 说明存在满足约束的生成树，输出树边；否则输出 NO。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2010;

int n, m, ec, dis[N], p[N], eu[N], ev[N];
bitset<N> b[N];
bool vis[N];
ll ans, tot;
char s[N];
int main() {
    int i, j, T; cin >> T;
    while (T--) {
        cin >> n >> m; ec = 0;
        rep(i,n) { b[i].reset(); vis[i] = 0; dis[i] = -1; }
        ans = 0;
        rep(i,m) {
            cin >> s; int cnt = 0;
            rep(j,n) if (s[j-1] == '1') b[j].set(i), cnt++;
            if (cnt > 1) ans += cnt - 1;
        }
        tot = 0; dis[1] = 0;
        rep(i,n) {
            int u = -1;
            rep(j,n) if (!vis[j] && (u == -1 || dis[j] > dis[u])) u = j;
            if (u == -1 || dis[u] == -1) break;
            tot += dis[u]; vis[u] = 1;
            if (p[u]) { eu[++ec] = p[u]; ev[ec] = u; }
            rep(j,n) if (!vis[j]) {
                int w = (b[j]&b[u]).count();
                if (w > dis[j]) dis[j] = w, p[j] = u;
            }
        }
        if (ec == n-1 && tot == ans) {
            cout << "YES\n";
            rep(i,ec) cout << eu[i] << ' ' << ev[i] << '\n';
        } else cout << "NO\n";
    }
    return 0;
}