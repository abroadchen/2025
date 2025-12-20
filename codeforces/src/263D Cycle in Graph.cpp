//
// Created by Psy.C on 2025/12/20.
//
/*
*dis[N]：存储节点的深度/距离
fa[N]：存储节点的父节点
k：环的最小长度要求
vis[N]：标记节点是否已访问
v[N]：邻接表表示图
*s：当前节点
x：当前深度
设置当前节点的深度和访问标记
*遍历当前节点的所有邻居：
如果邻居未访问过，设置父子关系并递归DFS
*计算当前节点与邻居节点的距离差
如果距离差大于等于k，说明找到了足够长的环
输出环的长度和节点序列
exit(0)直接终止程序
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

ll dis[N], fa[N], k; bool vis[N];
vector<ll> v[N];
void dfs(const ll s, const ll x) {
    dis[s] = x; vis[s] = true;
    for (auto i : v[s]) {
        if (!vis[i]) fa[i] = s, dfs(i, x + 1);
        const ll dist = abs(dis[i] - dis[s]);
        if (dist >= k) {
            ll ans = dist + 1;
            i = s;
            cout << ans << '\n';
            while (ans != 0) {
                cout << i << ' ';
                i = fa[i];
                ans--;
            }
            exit(0);
        }
    }
}

int main() {
    fast;
    ll n, e; cin >> n >> e >> k;
    for (ll i = 0, x, y; i < e; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 1);
    return 0;
}