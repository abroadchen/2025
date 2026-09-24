//
// Created by Psy.C on 2026/9/22.
//
/**
to：目标点，nxt：邻接表下一节点（链式前向星），v：剩余容量 (residual capacity)，w：费用
w = 容量，c = 费用。
同时建正反两条边（反向边容量 0、费用 -c），成对边用 i^1 相互索引，方便退流。cnt 从 0 开始，0^1=1, 1^1=0 配对正常，因为 0 和 1 是 bit xor 配对
dis 初始为 -1（表示不可达）。注意这里是求最长路（dis[to] < dis[x]+w），即把费用当收益最大化。
找到一条从 S 到 T 的最长收益路径后，找瓶颈容量 mn，cost += dis[T] * mn，然后沿路径正反边退流。
返回是否能继续增广；主函数 while(spfa()){} 直到找不到增广路为止。
因为是带负权边（反向边 -c）的最长路，用 SPFA（可处理负权），不能直接用 Dijkstra，所以这里选 SPFA。这是个经典但较慢的 MCMF 写法（SPFA 最坏情况下复杂度高，常用于 n 不大、流量小的题）
S 源点，T 汇点，s 是超级源点。
add(S, s, 4, 0)：S 到 s 容量 4、费用 0。说明最大流量为 4（总量是 4 个单位的某种"资源/路径"）。
每个元素 i 建立 4 个节点（x+0n, x+1n, x+2n, x+3n）

对每个 i (1..n)，用 i+0*n、i+1*n、i+2*n、i+3*n 表示该位置的4 个分层节点，代表某种"状态/层"
s → i+2*n：超级源到第 2 层（费用 0）。
i+0*n → i+2*n、i+1*n → i+2*n：0 层、1 层汇入 2 层。
i+2*n → i+3*n：容量 1、费用 1——这是唯一的计费边，即"使用/覆盖该节点"会产生 1 单位费用。容量 1 表示每个位置最多被覆盖一次（计费一次）。
i+3*n → T：3 层到汇点。
结合 S→s 容量 4，明显是"选 4 条路径/4 个序列，每个元素最多被选一次（计 1 费用），求最大收益（覆盖最多元素）"的模型。

各分层节点的连边逻辑（枚举 j>i）

对每个 i，向后找 j，加 inf 容量的 0 费用边，表示状态转移
规则1: num[i]-num[j] == 1 → i 到 j
规则2: num[j]-num[i] == 1 → 反向
规则3: num[i]%7 == num[j]%7 → i+3 -> j+0
规则4: num[i]%7 == num[j]%7 → i+0 -> j+0
规则5: num[i]==num[j] → i+1 -> j+1
这些连边定义了从当前元素到后续元素的状态转移关系，依据 num 的数值关系（差 1、同 mod 7、相等）在不同层之间转移。break 表示只连第一个满足条件的 j（最近的），防止边数爆炸
反复增广到不能再增广，cost 是累计"最大收益"。输出它
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

namespace mc_mf {
    constexpr int N = 1e4+5e3, M = 2e6, inf = 0x3f3f3f3f;
    struct node { int to, nxt, v, w; } e[M];
    int cnt, head[N];
    void add(int u, int v, int w, int c) {
        e[cnt].w = c, e[cnt].to = v, e[cnt].v = w, e[cnt].nxt = head[u], head[u] = cnt++;
        e[cnt].w = -c, e[cnt].to = u, e[cnt].v = 0, e[cnt].nxt = head[v], head[v] = cnt++;
    }
    int dis[N], S, T, fr[N], id[N], cost;
    bool vis[N];
    queue<int> q;
    bool spfa() {
        memset(dis, -1, sizeof dis); dis[S] = 0, q.push(S), vis[S] = true;
        while (!q.empty()) {
            int x = q.front(); q.pop(); vis[x] = false;
            for (int i = head[x]; i != -1; i = e[i].nxt) {
                if (!e[i].v) continue;
                if (dis[e[i].to] < dis[x] + e[i].w) {
                    dis[e[i].to] = dis[x] + e[i].w;
                    fr[e[i].to] = x; id[e[i].to] = i;
                    if (!vis[e[i].to]) vis[e[i].to] = true, q.push(e[i].to);
                }
            }
        }
        if (dis[T] == -1) return false;
        int x = T, mn = inf;
        while (x != S) mn = min(mn, e[id[x]].v), x = fr[x];
        cost += dis[T]*mn, x = T;
        while (x != S) e[id[x]].v -= mn, e[id[x]^1].v += mn, x = fr[x];
        return true;
    }
}
using namespace mc_mf;

int num[3010];
int main() {
    fast;
    int n; cin >> n;
    memset(head, -1, sizeof head);
    S = 4*n+1, T = 4*n+2;
    int s = 4*n+3; add(S, s, 4, 0);
    for (int i = 1; i <= n; ++i) cin >> num[i];
    for (int i = 1; i <= n; ++i) {
        add(s, i+2*n, inf, 0);
        add(i+0*n, i+2*n, inf, 0);
        add(i+1*n, i+2*n, inf, 0);
        add(i+2*n, i+3*n, 1, 1);
        add(i+3*n, T, inf, 0);
        for (int j = i+1; j <= n; ++j)
            if (num[i]-num[j] == 1) {
                add(i+3*n, j+1*n, inf, 0);
                break;
            }
        for (int j = i+1; j <= n; ++j)
            if (num[j]-num[i] == 1) {
                add(i+3*n, j+1*n, inf, 0);
                break;
            }
        for (int j = i+1; j <= n; ++j)
            if (num[i]%7 == num[j]%7) {
                add(i+3*n, j+0*n, inf, 0);
                break;
            }
        for (int j = i+1; j <= n; ++j)
            if (num[i]%7 == num[j]%7) {
                add(i+0*n, j+0*n, inf, 0);
                break;
            }
        for (int j = i+1; j <= n; ++j)
            if (num[i] == num[j]) {
                add(i+1*n, j+1*n, inf, 0);
                break;
            }
    }
    while (spfa()){}
    cout << cost << '\n';
    return 0;
}