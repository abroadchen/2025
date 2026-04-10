//
// Created by Psy.C on 2026/4/7.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, m, k, a[N], b[N], bel[N];
map<int, int> mp[N];///两点间是否有边
set<int> s;///当前未访问的节点集合
queue<int> q;
bool vis[N], ok[N];
int main() {
    fast;
    cin >> n >> m >> k;
    int deg = n - 1;//节点1理论上最多可以连接的节点数
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i];
        if (a[i] > b[i]) swap(a[i], b[i]);
        mp[a[i]][b[i]] = mp[b[i]][a[i]] = 1;//标记边存在
        if (a[i] == 1) --deg;//如果边连接到节点1，则减少可连接数
    }
    if (deg < k) return cout << "impossible", 0;//剩余连接数小于k
    for (int i = 2; i <= n; ++i) s.insert(i);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (vis[i]) continue;
        q.push(i); vis[i] = true;
        while (!q.empty()) {
            int x = q.front(); q.pop(); s.erase(x);//从集合中删除当前节点
            for (auto it = s.begin(); it != s.end(); ) {
                int v = *it;
                if (mp[x][v]) { ++it; continue; }//x和v之间有边
                //x和v之间没有边，合并它们（形成连通块）
                fa[find(v)] = find(x);
                if (!vis[v]) q.push(v), vis[v] = true;//标记访问
                it = s.erase(it);//从集合中删除v
            }
        }
    }
    int tot = 0;
    for (int i = 2; i <= n; ++i) if (find(i) == i) ++tot;//统计连通块数量
    for (int i = 2; i <= n; ++i) bel[i] = find(i);//记录每个节点所属连通块
    if (tot > k) return cout << "impossible", 0;
    for (int i = 2; i <= n; ++i) {
        if (mp[1][i]) continue;
        ok[bel[i]] = true;//标记该连通块可以通过节点1到达
    }
    for (int i = 2; i <= n; ++i)
        if (!ok[bel[i]]) return cout << "impossible", 0;//有连通块无法到达节点1
    cout << "possible";
    return 0;
}