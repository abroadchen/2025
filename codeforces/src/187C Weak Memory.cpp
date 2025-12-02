//
// Created by Psy.C on 2025/12/2.
//
/*N=100005（节点数上限），M=400005（边数上限）0x7fffffff（int类型的最大正值）
*n: 节点数量
m: 边数量
k: 特殊节点数量
s: 起点
e: 终点
ans: 最终答案（路径上的最大连续距离）
 *cap[i]: 从起点到节点i的最短距离
*head[N]: 每个节点的邻接表头指针
nxt[M]: 链式前向星的下一个节点指针
to[M]: 边的目标节点
 *g[i]: 标记节点i是否为特殊节点
 *优先队列，存储(pair<距离,节点>)，按距离升序排列（小根堆）
*f: 起点
t: 终点
ind: 边的索引
使用链式前向星存储图结构
 *
*Dijkstra算法主循环：
c: 当前距离
f: 当前节点
 *如果当前距离大于已记录的最短距离，则跳过（延迟删除）
 *更新路径上的最大连续距离
 *如果到达终点，则提前结束
*如果当前节点是特殊节点，则将距离重置为0
这意味着经过特殊节点后，后续的距离重新计算
*遍历当前节点的所有邻居：
如果找到更短的路径，则更新距离并加入队列
 *输出结果：如果终点不可达输出-1，否则输出路径上的最大连续距离
 *
*时间复杂度：O((n+m)log n)
空间复杂度：O(n+m)
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define M 400005
#define inf 0x7fffffff
#define ii pair<int, int>
using namespace std;

int n, m, k, s, e, ans;
int cap[N];
int head[N], nxt[M], to[M];
bool g[N];
priority_queue<ii, vector<ii>, greater<>> q;

void add(const int f, const int t, const int ind) {
    to[ind] = t; nxt[ind] = head[f]; head[f] = ind;
}

int main() {
    fast;
    cin >> n >> m >> k;
    fill(cap, cap + n + 1, inf);
    memset(head, -1, sizeof(head));
    for (int i = 0, x; i < k; ++i) {//读取k个特殊节点并标记
        cin >> x;
        g[x] = true;
    }
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        add(a, b, i<<1), add(b, a, i<<1|1);
    }
    //读取起点s和终点e 初始化起点距离为0 将起点加入优先队列
    cin >> s >> e; cap[s] = 0; q.emplace(0,s);
    while (!q.empty()) {
        int c = q.top().first;
        const int f = q.top().second; q.pop();
        if (c > cap[f]) continue;
        ans = max(ans, c);
        if (f == e) break;
        if (g[f]) c = 0;
        for (int i = head[f]; ~i; i = nxt[i]) {
            if (cap[to[i]] > c + 1) {
                cap[to[i]] = c + 1;
                q.emplace(c + 1, to[i]);
            }
        }
    }
    cout << (cap[e] == inf ? -1 : ans);
    return 0;
}