//
// Created by Psy.C on 2026/9/14.
//
/**
N = 2000：状态范围大小。
M = 1000：目标位置 = 0 的偏移基准。
inf = 0x3f3f3f3f：无穷大，用作"未访问"标记。
dis[i]：记录位置 i-M（即偏移后）到达目标的最短步数
读入 n（可能是目标温度/初始读数）和 k（可用砝码/步长个数）。
所有位置初始为 inf（未访问）。
读 k 个值 x，把位置 x - n + M 标记为步数 1。
关键：位置编码为 x - n + M，说明它把真实值映射到 [0, N] 数组。x - n 可能是"相对当前温度的偏移"，+M 是为了让下标非负。而目标 M 对应真实值 0（因为当 x - n = 0 时才正好落在 M = 1000）。

也就是：初始状态可能是 n，读入的每个 x 是"步长/可调值"，把 x 相对 n 的偏移作为起点
先把所有距离为 1 的节点（起点）入队 → 多源 BFS。
对队首 x：遍历所有"步长来源" i（dis[i]==1 表示 i 也是可用步长/起点）。
新位置 = x + i - M（即当前状态加上步长 i-M）。
若未访问，入队并更新距离 = dis[x]+1。
本质：每次可以"加上任意一个可用步长 (i - M)"，一步步从起点推向状态轴上的其他点，直到到达 M（即 0
dis[M] 是到达 0（目标）的最短步数。
若仍为 inf（无法到达）→ 输出 -1；否则输出步数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3, M = 1e3, inf = 0x3f3f3f3f;

int dis[N+5];
queue<int> q;
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i <= N; ++i) dis[i] = inf;
    for (int i = 1, x; i <= k; ++i) {
        cin >> x;
        dis[x-n+M] = 1;
    }
    for (int i = 0; i <= N; ++i)
        if (dis[i] == 1) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i <= N; ++i) {
            if (dis[i] == 1 && dis[x+i-M] == inf) {
                q.push(x+i-M);
                dis[x+i-M] = dis[x] + 1;
            }
        }
    }
    if (dis[M] == inf) cout << -1; else cout << dis[M];
    return 0;
}