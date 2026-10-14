//
// Created by Psy.C on 2026/10/14.
//
/**
t[i]：节点 i 被"到达"的时刻（从源点起算步数）。
v[i]：访问标记，避免重复入队。
ans：记录最大的 t，即答案"最远步数"
终止条件：q.empty() 时队列里没有待处理节点，返回。
取队首节点 o 处理，并让 ans 取 t[o] 与当前的最大值（因为 BFS 按层扩展，越晚到队的节点步数越大，ans 最终等于最后入队节点的步数）。
向左右两边扩展：只要邻居在 [1, n] 范围内且未访问过，就标记访问、记录 t = t[o]+1、入队。
递归下一个队首 q.front()
有多组测试数据 T。
每组清空 v、t、q，ans 重置为 -1。
读入 n（节点数）与 k（源点个数）。
读入 k 个源点位置 l，全部标记访问、t[l]=1、入队（多源点 BFS）。
调用 dfs(q.front()) 开始扩散。
输出答案 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 205;

queue<int> q;
int ans, t[N], n;
bool v[N];
void dfs(int x) {
    if (q.empty() == 1) return;
    int o = q.front(); q.pop();
    ans = max(ans, t[o]);
    if (o-1 >= 1 && v[o-1] == 0) {
        v[o-1] = 1;
        t[o-1] = t[o] + 1;
        q.push(o-1);
    }
    if (o+1 <= n && v[o+1] == 0) {
        v[o+1] = 1;
        t[o+1] = t[o] + 1;
        q.push(o+1);
    }
    dfs(q.front());
}


int main() {
    fast;
    int T, k, l; cin >> T;
    while (T--) {
        memset(v, 0, sizeof(v));
        memset(t, 0, sizeof(t));
        while (!q.empty()) q.pop();
        ans = -1;
        cin >> n >> k;
        for (int i = 1; i <= k; ++i) { cin >> l; t[l] = 1; v[l] = 1; q.push(l); }
        dfs(q.front());
        cout << ans << '\n';
    }
    return 0;
}