//
// Created by Psy.C on 2026/2/25.
//
/**
v(n)：存储n个节点的信息
ans：存储结果序列

v[i].first：节点i的度数（入度）
v[i].second：节点i指向的节点编号
将所有入度为1的节点加入队列，作为BFS的起点

将x指向的节点的入度减1
对x指向的节点的异或值进行更新（拓扑排序中的技巧）
将处理的边{x, v[x].second}加入结果序列
如果x指向的节点入度变为1，将其加入队列

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

ll n;
queue<ll> q;
int main() {
    fast;
    cin >> n;
    vector<pll> v(n), ans;
    for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
    for (int i = 0; i < n; ++i)
        if (v[i].first == 1) q.push(i);
    while (!q.empty()) {
        ll x = q.front(); q.pop();
        if (v[x].first == 0) continue;
        v[v[x].second].first--;
        v[v[x].second].second ^= x;
        ans.push_back({x, v[x].second});
        if (v[v[x].second].first == 1)
            q.push(v[x].second);
    }
    cout << ans.size() << '\n';
    for (auto&[fst, snd] : ans)
        cout << fst << ' ' << snd << '\n';
    return 0;
}