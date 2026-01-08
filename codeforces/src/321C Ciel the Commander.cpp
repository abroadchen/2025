//
// Created by Psy.C on 2026/1/7.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

vector<int> g[N];//存储树结构
bool vis[N];

int dfs2(const int u, const int p) {//以u为根的连通块的大小
    if (vis[u]) return 0;
    int sum = 1;//包含节点u自己
    for (const auto v : g[u]) {
        if (v != p) sum += dfs2(v, u);//累加子树大小
    }
    return sum;
}

/**
 *
 * @param u
 * @param p
 * @param tot 连通块总大小
 * @param w 返回重心节点
 * @return
 */
int dfs3(const int u, const int p, const int tot, int& w) {//寻找重心并更新重心节点
    if (vis[u]) return 0;
    int sum = 1, mx = 0;//子树大小和最大子树大小
    for (const auto v : g[u]) {
        if (v == p) continue;
        int t = dfs3(v, u, tot, w);
        mx = max(mx, t);
        sum += t;
    }
    mx = max(mx, tot - sum);//删除当前节点后，剩余部分的大小
    if (mx <= tot / 2) w = u;//满足重心条件，更新重心
    return sum;
}


char s[N];//每个节点对应字母
void dfs(int u, const char c) {
    if (vis[u]) return;
    dfs3(u, -1, dfs2(u, -1), u);
    vis[u] = true;
    s[u] = c;//为重心分配字母
    for (const auto v : g[u]) dfs(v, static_cast<char>(c + 1));//递归处理子连通块，字母+1
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, 'A');
    for (int i = 1; i <= n; ++i) { cout << s[i] << ' '; }
    return 0;
}