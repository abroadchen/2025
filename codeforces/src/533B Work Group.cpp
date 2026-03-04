//
// Created by Psy.C on 2026/3/3.
//
/**
DFS函数处理以u为根的子树
初始化dp[u][1] = -inf
len = e[u].size(): 获取u的子节点数量
如果是叶子节点（len==0）:
dp[u][1] = a[u]: 选择该节点
dp[u][0] = 0: 不选择该节点
遍历所有子节点v:
保存当前状态值t0, t1
更新状态转移方程
dp[u][1]: 表示当前节点与子节点状态不同的最大值
dp[u][0]: 表示当前节点与子节点状态相同的最大值
最后更新dp[u][1]，考虑选择当前节点的情况

循环读入每个节点的父节点x和权值a[i]
x != -1: 如果不是根节点(-1表示根节点)，则建立父子关系
e[x].push_back(i): 在x的邻接表中添加子节点i
dp[1][1]，即整个树在状态1下的最优解

时间复杂度为O(n)，空间复杂度为O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+1, inf = 0x3f3f3f3f;
vector<int> e[N];///树的边
ll dp[N][3];///dp[u][0/1]表示节点u的状态
int a[N];///每个节点的权值
void dfs(const int u) {
    dp[u][1] = -inf;
    const int len = e[u].size();
    if (len == 0) {
        dp[u][1] = a[u]; dp[u][0] = 0; return;
    }
    for (int i = 0; i < len; ++i) {
        const int v = e[u][i]; dfs(v);
        const ll t1 = dp[u][1], t0 = dp[u][0];
        dp[u][1] = max(t0+dp[v][1], t1+dp[v][0]);
        dp[u][0] = max(t0+dp[v][0], t1+dp[v][1]);
    }
    dp[u][1] = max(dp[u][1], dp[u][0]+a[u]);
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x >> a[i];
        if (x != -1) e[x].push_back(i);
    }
    dfs(1);
    cout << dp[1][1] << '\n';
    return 0;
}