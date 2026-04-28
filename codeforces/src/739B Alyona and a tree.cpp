//
// Created by Psy.C on 2026/4/28.
//
/**
nxt[]: 邻接表中下一个节点的索引
head[]: 每个节点邻接表的头指针
v[]: 边的目标节点
w[]: 边的权重
cnt: 边的计数器
dep[]: 节点深度
f[][]: 倍增数组，f[i][j]表示节点i向上跳2^j步到达的节点
dis[]: 从根节点到当前节点的距离

建立树结构，计算每个节点的深度、父节点和距离
遍历当前节点的所有邻接节点
跳过父节点或已访问过的节点
更新子节点的深度、父节点和距离
递归遍历子节点

a[]: 每个节点的限制值
ans[]: 每个节点的答案（差分数组）
从节点x开始，尽可能向上跳跃（在距离不超过a[x]的条件下）
使用倍增思想，从高位到低位尝试跳跃
更新差分数组（用于统计影响范围）
从叶子节点向上累加答案
将子节点的贡献加到当前节点上

读入节点数n
读入每个节点的限制值a[i]
从第2个节点开始，读入父节点p和边权w，建立树结构
从根节点1开始DFS，建立深度、距离和倍增数组
建立完整的倍增数组（倍增预处理）
对每个节点计算其影响范围并更新差分数组
从根节点开始第二次DFS，累加答案
输出每个节点的最终答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 3e5;

int nxt[N], head[N], v[N], w[N], cnt;
void add(int fr, int to, int val) {
    nxt[++cnt] = head[fr]; head[fr] = cnt;
    v[cnt] = to; w[cnt] = val;
}

int dep[N], f[N][35], dis[N];
void dfs(int x, int fa) {
    for (int i = head[x]; i; i = nxt[i]) {
        int to = v[i];
        if (to == fa || dep[to]) continue;
        dep[to] = dep[x] + 1;
        f[to][0] = x;
        dis[to] = dis[x] + w[i];
        dfs(to, x);
    }
}

int a[N], ans[N];
void get(int x) {
    int g = x;
    for (int i = 32; i >= 0; --i)
        if (f[g][i] && dis[x] - dis[f[g][i]] <= a[x])
            g = f[g][i];
    ans[f[g][0]]--; ans[f[x][0]]++;
}

void dfs2(int x) {
    for (int i = head[x]; i; i = nxt[i]) {
        int to = v[i];
        dfs2(to);
        ans[x] += ans[to];
    }
}

int n;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2, p, w; i <= n; ++i) {
        cin >> p >> w;
        add(p, i, w);
    }
    dfs(1, -1);
    for (int j = 1; j <= 32; ++j)
        for (int i = 1; i <= n; ++i)
            f[i][j] = f[f[i][j-1]][j-1];
    for (int i = 1; i <= n; ++i) get(i);
    dfs2(1);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}