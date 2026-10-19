//
// Created by Psy.C on 2026/10/19.
//
/**
从起点做 BFS，计算源到各点的最短距离存入 d，之后清空访问标记和队列（复用同一队列/数组跑第二次 BFS）
枚举所有原来不存在的候选边 (i,j)（i<j），计算加边后形成的新路径 s→i +1边+ j→t（两个方向取 min），只要它不短于原最短路 d1[t]，说明加这条边不会缩短 s→t 的距离，计数 +1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1010;

int chkmin(int x, int y) { return x < y ? x : y; }

int n, to[N][N];
queue<int> q;
bool vis[N];
void bfs(int *d) {
    while (!q.empty()) {
        int now = q.front(); q.pop();
        rep(i,1,n) {
            if (!to[now][i] || vis[i]) continue;
            vis[i] = true, d[i] = d[now]+1, q.push(i);
        }
    }
    //重置 vis 和 q
    rep(i,1,n) vis[i] = false;
    while (!q.empty()) q.pop();
}

int m, s, t, x, y, d1[N], d2[N], cnt;
int main() {
    fast;
    cin >> n >> m >> s >> t;//n点 m边，求 s 到 t 的"加边不缩最短路"
    rep(i,1,m) cin >> x >> y, to[x][y] =1, to[y][x] = 1;
    vis[s] = true, q.push(s), bfs(d1);//d1 = 从 s 出发的最短路
    vis[t] = true, q.push(t), bfs(d2);//d2 = 从 t 出发的最短路
    rep(i,1,n) rep(j,i,n) {
        if (i == j || to[i][j]) continue;//只考虑 i<j 的"非现有边"
        //加边 (i,j)，走 s→i→j→t 的距离 另一方向 s→j→i→t
        int a1 = d1[i]+1+d2[j], a2 = d1[j]+1+d2[i];
        cnt += chkmin(a1, a2) >= d1[t];//若新路不短于原最短路，则这条边"合法"可加
    }
    cout << cnt;
    return 0;
}