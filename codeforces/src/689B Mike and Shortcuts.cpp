//
// Created by Psy.C on 2026/4/15.
//
/**
n1, n2, n3：当前节点的三个邻居节点
sf：当前节点编号（self）
vis：访问标记数组
d：距离数组，存储从起点到各节点的最短距离

初始化队列：将起始节点加入队列
遍历邻居：对每个节点的三个邻居进行BFS扩展
距离更新：每个未访问邻居的距离 = 当前节点距离 + 1
条件检查：只处理未访问且存在的邻居（n3可能为0）

每个节点i连接到i-1（左邻居）和i+1（右邻居）
读取特殊边目标x，如果x≠i，则添加特殊边i→x
设置节点编号sf=i
从节点1开始BFS：寻找最短路径
输出距离：输出从节点1到每个节点的最短距离

时间复杂度：O(n)，每个节点最多访问一次
空间复杂度：O(n)，存储图和BFS队列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

struct node { int n1, n2, n3, sf; } e[N];

int vis[N], d[N];
void bfs(node s) {
    queue<node> q; q.push(s); vis[1] = 1;
    node n{};
    while (!q.empty()) {
        n = q.front(); q.pop();
        if (!vis[n.n1]) {
            q.push(e[n.n1]);
            vis[n.n1] = 1;
            d[n.n1] = d[n.sf] + 1;
        }
        if (!vis[n.n2]) {
            q.push(e[n.n2]);
            vis[n.n2] = 1;
            d[n.n2] = d[n.sf] + 1;
        }
        if (n.n3 && !vis[n.n3]) {
            q.push(e[n.n3]);
            vis[n.n3] = 1;
            d[n.n3] = d[n.sf] + 1;
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        e[i].n1 = i-1; e[i].n2 = i+1; e[i].n3 = 0;
        e[i].sf = i;
        cin >> x;
        if (x != i) e[i].n3 = x;
    }
    bfs(e[1]);
    for (int i = 1; i <= n; ++i) cout << d[i] << ' ';
    cout << '\n';
    return 0;
}