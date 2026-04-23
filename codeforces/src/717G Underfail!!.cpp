//
// Created by Psy.C on 2026/4/22.
//
/**
to：边指向的节点
nxt：链式前向星的下一个边的索引
cap：边的容量
flow：边的实际流量
cost：边的单位流量费用
head[u]：以u为起点的最后一条边的索引
cnt：边的总数计数器

使用SPFA算法找从源点s到汇点t的最短路径
dis[i]：从源点到节点i的最短距离
pre[i]：记录到达节点i的边索引
只考虑还有剩余容量的边(e[i].cap > e[i].flow)
返回是否存在增广路径
不断寻找最短增广路径直到无法找到
找到路径上的最小残余容量mn
更新路径上每条边的流量和总费用
e[i^1]获取反向边（利用异或特性：奇数^1=偶数，偶数^1=奇数）

读入字符串长度n和目标字符串s
获取字符串长度l，初始化网络（l+2个节点）
读入模式串的数量m
对每个模式串s1，价值为v
在主串s中查找所有匹配位置
如果在位置j开始匹配成功，添加边(j, j+l1, 1, -v)
注意费用是-v（因为求最大收益，转换为最小费用问题）
连接相邻字符位置，容量无限，费用为0
允许"跳过"未被模式串覆盖的位置
源点0到起始位置1，容量为x（限制匹配次数）
最后位置l到汇点l+1，容量无限
从源点0到汇点l+1跑最小费用最大流
因为费用是负的（-v），所以最终结果要取负号
输出最大收益
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 507, inf = 0x3f3f3f3f;

struct edge { int to, nxt, cap, flow, cost; } e[N*N];

int head[N], cnt;
void add(int u, int v, int cap, int cost) {
    e[cnt] = {v, head[u], cap, 0, cost}, head[u] = cnt++;
    e[cnt] = {u, head[v], 0, 0, -cost}, head[v] = cnt++;
}

int n;
void init(int _n) {
    n = _n; cnt = 0;
    memset(head, -1, sizeof(head));
}

int dis[N], pre[N];
bool vis[N];
bool spfa(int s, int t) {
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        dis[i] = inf; vis[i] = false; pre[i] = -1;
    }
    dis[s] = 0; vis[s] = true; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            int v = e[i].to;
            if (e[i].cap > e[i].flow && dis[v] > dis[u] + e[i].cost) {
                dis[v] = dis[u] + e[i].cost;
                pre[v] = i;
                if (!vis[v]) { vis[v] = true; q.push(v); }
            }
        }
    }
    if (pre[t] == -1) return false;
    return true;
}

int mc_mf(int s, int t, int& cost) {
    int flow = 0; cost = 0;
    while (spfa(s, t)) {
        int mn = inf;
        for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
            if (mn > e[i].cap - e[i].flow)
                mn = e[i].cap - e[i].flow;
        }
        for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
            e[i].flow += mn;
            e[i^1].flow -= mn;
            cost += e[i].cost*mn;
        }
        flow += mn;
    }
    return flow;
}

char s[N], s1[110];
int main() {
    scanf("%d", &n); scanf("%s", s + 1);
    int l = strlen(s + 1); init(l + 2);
    int m; scanf("%d", &m);
    for (int i = 1, v; i < m+1; ++i) {
        scanf("%s", s1 + 1);
        scanf("%d", &v);
        int l1 = strlen(s1 + 1);
        for (int j = 1; j <= l-l1+1; ++j) {
            bool f = true;
            for (int k = 1; k <= l1; ++k)
                if (s[j+k-1] != s1[k]) {
                    f = false;
                    break;
                }
            if (f) add(j, j+l1, 1, -v);
        }
    }
    for (int i = 1; i < l; ++i) add(i, i+1, inf, 0);
    int x; scanf("%d", &x);
    add(0, 1, x, 0), add(l, l+1, inf, 0);
    int ans = 0;
    mc_mf(0, l+1, ans);
    printf("%d\n", -ans);
    return 0;
}