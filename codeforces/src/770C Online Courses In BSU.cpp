//
// Created by Psy.C on 2026/9/8.
//
/**
e[] 存储每条边：fr 起点、to 终点、pre 指向上一条同起点的边（head 链）。
add(fr, to) 把边插入到 head[fr] 链头
vis[N]：标记某个节点是否已加入答案（已完成后置 true）。
vis_dfs[N]：标记正在 DFS 访问中（用于检测环）。
ans：队列，按完成后顺序存放答案

if (vis_dfs[now])：如果当前节点正处于 DFS 递归栈中（即又被再次访问到），说明存在环，无法进行拓扑排序，输出 -1 并结束程序。
vis_dfs[now] = true：标记当前节点入栈。
遍历它的所有后继 v：若 v 尚未完成（!vis[v]），递归 dfs(v)（先处理依赖）。
全部后继处理完后：vis[now]=true（标记完成）并把 now 压入答案队列 ans

读入 n（节点数）和 m（初始要完成/关注的节点数）。
第一个循环读入 m 个数 t，全部压入队列 q（这些是需要执行/纳入考虑的任务）。
第二个循环：对每个节点 i，读入其依赖个数 t，然后读入 t 个依赖编号 id，建边 add(i, id)——即 i 依赖 id（要完成 i 先要完成 id）
对初始队列里的每个任务 x，若还没完成（!vis[x]）就调用 dfs(x) 处理它及它的全部依赖。
这样把涉及的所有"必要任务"连同它们的依赖一起做拓扑排序
输出答案队列的大小，再依次输出队列中各任务编号（即最终合法完成顺序）。
若中途检测到环则早已输出 -1 退出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct edge { int fr, to, pre; } e[N];
int cnt, head[N];
void add(int fr, int to) {
    e[++cnt].fr = fr; e[cnt].to = to; e[cnt].pre = head[fr]; head[fr] = cnt;
}

bool vis[N], vis_dfs[N];
queue<int> ans;
void dfs(int now) {
    if (vis_dfs[now]) { cout << "-1\n"; exit(0); }
    vis_dfs[now] = true;
    for (int i = head[now]; i; i = e[i].pre) {
        int v = e[i].to;
        if (!vis[v]) dfs(v);
    }
    vis[now] = true;
    ans.push(now);
}

queue<int> q;
int main() {
    fast;
    int n, m, t, id; cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> t; q.push(t);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> t;
        while (t--) {
            cin >> id; add(i, id);
        }
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (!vis[x]) dfs(x);
    }
    cout << ans.size() << '\n';
    while (!ans.empty()) cout << ans.front() << ' ', ans.pop();
    cout << '\n';
    return 0;
}