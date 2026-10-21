//
// Created by Psy.C on 2026/10/21.
//
/**
dfn/low：Tarjan 时间戳与 low 值。
tot：时间戳计数；st/top：用作边的栈。
scc：连通分量计数。
tmp：当前分量内的边缓存。
u[i]/w[i]：第 i 条边（无向边）的两个端点，用边编号作为栈元素。
mp：用于给"顶点"按所在分量打标（去重判断顶点来自哪个分区）。
v[x]：邻接表，存 (邻居, 边编号)。
ans：收集满足条件的边
标记 dfn[x]=low[x]=++tot。
遍历邻接边 (y, id)：
if (id == p) continue;：跳过父边（p 是进入本节点的边编号，防止走回）。
树边（!dfn[y]）：
把边 id 压栈 st[++top]=id，递归 tarjan(y, id)，更新 low。
若 low[y] >= dfn[x]：说明以 x 为"割点"界定出一个边双/连通分量边界，++scc 开一个新分量：
从栈顶弹出边，放入 tmp[1..cnt]；
用 mp 给每条边两端顶点打上 scc 标记并计数 cv（去重后的顶点数，因为同一条边两端、以及共享顶点的边会去重）；
若 cnt == cv（边数 == 去重顶点数）则把这 cnt 条边全部加入 ans。
回边（dfn[y] < dfn[x]，即指向祖先）：把边 id 压栈，low[x]=min(low[x],dfn[y])
读入 n 顶点、m 边；对每条无向边 (x,y) 记 u[i]=x, w[i]=y，并在 x、y 邻接表都加入 (... , i)。
对每个未访问顶点跑 tarjan。
排序 ans，输出数量与边编号列表
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int dfn[N], low[N], tot, st[N], top, scc, tmp[N], u[N], w[N], mp[N];
vector<ii> v[N];
vector<int> ans;
void tarjan(int x, int p) {
    dfn[x] = low[x] = ++tot;
    for (auto [fst, snd] : v[x]) {
        int y = fst, id = snd;
        if (id == p) continue;
        if (!dfn[y]) {
            st[++top] = id; tarjan(y, id); low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x]) {
                ++scc;
                int cnt = 0, cv = 0;
                while (true) {
                    int e = st[top--]; tmp[++cnt] = e;
                    if (mp[u[e]] != scc) mp[u[e]] = scc, cv++;
                    if (mp[w[e]] != scc) mp[w[e]] = scc, cv++;
                    if (e == id) break;
                }
                if (cnt == cv)
                    for (int i = 1; i <= cnt; i++) ans.push_back(tmp[i]);
            }
        } else if (dfn[y] < dfn[x]) {
            st[++top] = id;
            low[x] = min(low[x], dfn[y]);
        }
    }
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y; u[i] = x; w[i] = y;
        v[x].emplace_back(y, i); v[y].emplace_back(x, i);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
    ranges::sort(ans);
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    cout << '\n';
    return 0;
}