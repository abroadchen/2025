//
// Created by Psy.C on 2026/1/21.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105000
#define M 1500000
using namespace std;

struct node { int st, to, w, nxt; } e[M];
int cnt, head[N];
void add(const int st, const int to, const int w) {
    e[cnt].to = to; e[cnt].w = w; e[cnt].nxt = head[st]; head[st] = cnt++;
}

int dp[N];//以u为根的子树中能达到的最大边权值
void dfs(const int u, const int st) {//每个节点及其子树中的最大边权值
    dp[u] = 0;
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        const int v = e[i].to, w = e[i].w;
        dp[u] = max(dp[u], w);//当前节点的最大边权
        if (v == st) continue;
        dfs(v, u);
        dp[u] = max(dp[u], dp[v]);//当前节点的最大子树权值
    }
}

int d[N];
void dfs(const int u, const int st, const int sum) {
    if (sum == 1) d[u] = 1;//如果边权为1，标记当前节点
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        const int v = e[i].to, w = e[i].w;
        if (v == st) continue;
        dfs(v, u, w);//传递当前边权作为下一层的"sum"
        if (dp[v] == 1) d[u] = 0;//子树最大权值为1，取消当前节点标记
    }
}

int main() {
    fast;
    int n; cin >> n; int tot = 0;
    memset(d, 0, sizeof d);
    memset(dp, 0, sizeof dp);
    memset(head, -1, sizeof head);
    for (int i = 0, x, y, w; i < n - 1; ++i) {
        cin >> x >> y >> w; add(x, y, w-1);
        add(y, x, w-1);
    }
    dfs(1, -1); dfs(1, -1, 0);
    int ans[N];
    for (int i = 1; i <= n; ++i) if (d[i] == 1) ans[tot++] = i;
    cout << tot << '\n';
    for (int i = 0; i < tot; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}