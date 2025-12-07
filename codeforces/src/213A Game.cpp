//
// Created by Psy.C on 2025/12/6.
//
/*
*c[N]：每个节点的任务类型（1, 2, 或 3）
d[N]：每个节点的入度
b[N]：入度的备份数组
 *
*多队列管理：为每种类型的任务维护独立队列q[1], q[2], q[3]
轮转调度：按照1→2→3→1的顺序轮流处理各类任务
参数k：指定从哪一类任务开始处理
 *
*初始化：将所有入度为0的节点按类型放入对应队列
循环处理：按类型顺序处理可用任务
每处理完一轮（一种类型）增加时间单位
更新依赖关系，将新变为入度0的节点加入对应队列
 *
 *O(n³)：3次BFS，每次O(n²)
 */
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 210
using namespace std;

constexpr int inf = 0x3f3f3f3f;
int n;

struct node { int to, nxt; } r[N*N];

int head[N], cnt;
void add(const int u, const int v) {
    r[cnt].to = v, r[cnt].nxt = head[u], head[u] = cnt++;
}

int c[N], d[N], b[N];

int bfs(int k) {
    queue<int> q[4]; int ans = 0;
    memcpy(b, d, sizeof(d));
    for (int i = 1; i <= n; ++i) if (!d[i]) q[c[i]].push(i);
    while (!q[1].empty() || !q[2].empty() || !q[3].empty()) {
        while (!q[k].empty()) {
            const int u = q[k].front(); q[k].pop();
            ans++;//执行任务
            for (int i = head[u]; ~i; i = r[i].nxt) {
                int v = r[i].to;
                if (--d[v] == 0) q[c[v]].push(v);
            }
        }
        k = k % 3 + 1;
        ans++;//类型切换也需要1个时间单位（即使没有任务执行）
    }//如果d[i] > 0，说明任务i还有未完成的前置任务
    for (int i = 1; i <= n; ++i) if (d[i]) ans = inf;
    memcpy(d, b, sizeof(d));
    return ans - 1;//最后一次类型切换后不再需要切换时间
}

int main() {
    fast;
    cin >> n;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1, k, j; i <= n; ++i) {
        cin >> k;
        while (k--) {
            cin >> j;
            add(j, i);//j是i的前置任务
            d[i]++;
        }
    }
    int res = inf;
    for (int i = 1; i <= 3; ++i) res = min(bfs(i), res);
    cout << res << '\n';
    return 0;
}