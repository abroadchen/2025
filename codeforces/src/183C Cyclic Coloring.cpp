//
// Created by Psy.C on 2025/12/1.
//
/*
*k: 存储所有环权重的最大公约数
f[N]: 记录到达每个节点时的累计权重
 *
 *u是当前节点，cnt是到达u时的累计权重
*如果节点u已经被访问过，说明找到了一个环
环的权重是当前累计权重cnt减去之前访问u时的权重f[u]
更新k为当前k与环权重的最大公约数
void()用于结束函数执行
 *
 *遍历从节点u出发的所有边，~i表示i不等于-1
 *递归访问目标节点v，累计权重加上当前边的权重w[i]
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

int n, m, head[N], vis[N];

int nxt[N<<1], ed[N<<1], w[N<<1], idx;
void add(const int u, const int v, const int c) {
    nxt[++idx] = head[u];
    ed[idx] = v;
    w[idx] = c;
    head[u] = idx;//更新head[u]指向新添加的边
}

int k, f[N];
void dfs(const int u, const int cnt) {
    if (vis[u]) return k = __gcd(k, cnt - f[u]), void();
    vis[u] = 1;
    f[u] = cnt;//记录到达节点u时的累计权重
    for (int i = head[u]; ~i; i = nxt[i]) {
        const int v = ed[i];
        dfs(v, cnt + w[i]);
    }
}

int main() {
    fast;
    memset(head, -1, sizeof(head));//空链表
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        add(u, v, 1); add(v, u, -1);//每条无向边在正反方向有不同的权重
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 0);
    cout << (k == 0 ? n : abs(k));//如果k为0（没有环）则输出n，否则输出k的绝对值
    return 0;
}