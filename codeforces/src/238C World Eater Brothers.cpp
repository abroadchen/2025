//
// Created by Psy.C on 2025/12/13.
//
/*
*dp[N]存储动态规划值
mx存储最大值
DFS遍历树：
对每个子节点递归调用dfs
dp[u]累加子节点的dp值和边的权重
(e[i].dis != 1)如果边权不为1则加1
更新mx为当前val和mx的最大值
 *
*初始化邻接表
读入n-1条边，每条边添加两条有向边：
正向边权为1
反向边权为-1
 *
*枚举每条边，计算以这条边为分割点时的最优值：
对边的两个端点分别进行DFS
计算总代价并更新最小值
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define inf 10000001
using namespace std;

struct node { int st, to, dis, nxt; } e[N<<1];

int head[N], cnt;
void add(const int u, const int v, const int d) {
    e[cnt] = {u, v, d, head[u]};
    head[u] = cnt++;
}

int dp[N], mx;
void dfs(const int u, const int fa, const int val) {
    dp[u] = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        const int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u, val - e[i].dis);
        dp[u] += dp[v] + (e[i].dis != 1);
    }
    mx = max(mx, val);
}


int main() {
    fast;
    int n, u, v; cin>>n;
    if (n == 1) { cout << "0" << '\n'; return 0; }//只有一个节点
    memset(head, -1, sizeof(head)); cnt = 0;
    for (int i = 1; i < n; ++i) {
        cin>>u>>v; add(u, v, 1); add(v, u, -1);
    }
    int ans = inf;
    for (int i = 0; i < cnt; i += 2) {
        u = e[i].st, v = e[i].to, mx = -inf;
        dfs(u, v, 0);
        int t = dp[u] - mx; mx = -inf;
        dfs(v, u, 0);
        t += dp[v] - mx;
        ans = min(ans, t);
    }
    cout<<ans<<'\n';
    return 0;
}