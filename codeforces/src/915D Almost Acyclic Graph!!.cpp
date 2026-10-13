//
// Created by Psy.C on 2026/10/13.
//
/**
标准 Kahn 算法：把入度为 0 的点入队并标记 v；每次弹出队首 now，将其所有出边的终点入度 in[i]--；再把新出现的入度 0 且未被处理过的点入队。
cnt 统计成功出队的点数。若 cnt == n，说明所有点都被拓扑排序，图是 DAG → 返回 true；否则有环 → 返回 false
读入 n 个点、m 条有向边，建图并累加入度 in[]；用 t[] 备份初始入度（供每次尝试后还原）。
先判断原图是否已无环（topp() 返回 true），若是直接输出 `YES"
遍历每个点 i：若 in[i] > 0（存在入边），把它减 1 模拟"删除某条指向 i 的边"，再跑一次 topp()；一旦无环即输出 YES。每次尝试后都还原回初始入度 t[]。
所有点试完仍不能无环，输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 550;

bool v[N];
int n, in[N];
vector<int> g[N];
bool topp() {
    memset(v, false, sizeof(v));
    queue<int> q;
    rep(i,1,n) if (in[i] == 0) { v[i] = true; q.push(i); }
    int cnt = 0;
    while (!q.empty()) {
        int now = q.front(); q.pop(); cnt++;
        for (int i : g[now]) in[i]--;
        rep(i,1,n) if (in[i] == 0 && !v[i]) { q.push(i); v[i] = true; }
    }
    if (cnt == n) return true;
    return false;
}

int m, t[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,m) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); in[v]++;
    }
    rep(i,1,n) t[i] = in[i];
    if (topp()) { cout << "YES"; return 0; }
    rep(i,1,n) in[i] = t[i];
    rep(i,1,n) if (in[i]) {
        in[i]--;
        if (topp()) { cout << "YES"; return 0; }
        rep(j,1,n) in[j] = t[j];
    }
    cout << "NO";
    return 0;
}