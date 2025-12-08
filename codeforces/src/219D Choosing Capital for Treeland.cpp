//
// Created by Psy.C on 2025/12/8.
//
/*
*tot：边的总数计数器
to[N<<1]：存储每条边的终点节点（N<<1表示N*2）
w[N<<1]：存储边的权重
nxt[N<<1]：链式前向星的next指针
head[N<<1]：每个节点的第一条边
add函数：添加从u到v权重为x的有向边
 *
*第一次DFS（树形DP）：计算以节点1为根时各节点的dp值
dp[x]：节点x的dp值
从节点x的邻接表开始遍历所有相连的边
v：当前边指向的节点
跳过父节点fa
递归处理子节点v
状态转移：dp[x] += dp[v] + (w[i] == 0)
如果边权重为0则加1，否则加0
 *
*第二次DFS（换根DP）：重新计算以其他节点为根时的dp值
换根时dp值的变化规律：
如果边权重为1：dp[v] = dp[u] + 1
如果边权重为0：dp[v] = dp[u] - 1
递归处理子节点
 *
*ans：最小dp值，初始化为极大值
执行两次DFS计算所有节点的dp值
遍历所有节点找出dp值最小的节点
如果找到更小值则更新ans并清空结果集
如果值相等则添加到结果集中
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200002
using namespace std;

int tot, to[N<<1], w[N<<1], nxt[N<<1], head[N<<1];
void add(const int u, const int v, const int x) {
    to[++tot] = v; w[tot] = x; nxt[tot] = head[u]; head[u] = tot;
}

int dp[N];
void dfs(const int x, const int fa) {
    for (int i = head[x]; i; i = nxt[i]) {
        const int v = to[i];
        if (v == fa) continue;
        dfs(v, x);
        dp[x] += dp[v] + (w[i] == 0);
    }
}

void dfs2(const int u, const int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        const int v = to[i];
        if (v == fa) continue;
        if (w[i] == 1) dp[v] = dp[u] + 1;
        else dp[v] = dp[u] - 1;
        dfs2(v, u);
    }
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i < n; ++i) {//读取n-1条边，构建树结构
        cin >> u >> v;
        add(u, v, 1); add(v, u, 0);
    }
    int ans = 1e9; dfs(1, 0); dfs2(1, 0);
    vector<int> res;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] < ans) {
            ans = dp[i];
            res.clear();
            res.push_back(i);
        } else if (dp[i] == ans) res.push_back(i);
    }
    cout << ans << '\n';
    for (const int re : res) cout << re << ' ';
    return 0;
}