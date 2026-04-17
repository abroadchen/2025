//
// Created by Psy.C on 2026/4/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5, M = 1e4+5;
struct node { int nd, nxt; } e[N];
///head[i]表示节点i的第一条边的索引
int head[M], cnt;
void add(int x, int y) {
    e[cnt] = {y, head[x]}, head[x] = cnt++;
}

int ans, vis[M];
void dfs(int st, int dep) {
    if (dep == 2) { ans++; return; }
    if (!vis[st]) {//当前节点未被访问过
        //遍历从当前节点出发的所有边
        for (int i = head[st]; i != -1; i = e[i].nxt) {
            if (!vis[e[i].nd]) {//下一个节点未被访问
                vis[st] = 1;//当前节点为已访问
                dfs(e[i].nd, dep + 1);//递归搜索下一个节点，深度+1
            }
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    memset(head, -1, sizeof(head));
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        add(a, b); add(b, a);
    }
    ans = 0;
    for (int i = 1; i <= n; ++i) {//从每个节点开始做DFS
        memset(vis, 0, sizeof(vis));
        dfs(i, 0);
    }
    cout << ans/2;//无向图每条路径被计算了两次
    return 0;
}