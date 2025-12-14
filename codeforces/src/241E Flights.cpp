//
// Created by Psy.C on 2025/12/14.
//
/*
*to[]: 边的目标节点
nxt[]: 下一条边的索引
w[]: 边的权重
head[]: 每个节点的第一条边
cnt: 边的计数器
add(): 添加边的函数，构建邻接表
 *
*用于检测负环，判断差分约束系统是否有解
vis[]: 节点是否在队列中
c[]: 节点入队次数
d[]: 到源点的最短距离
如果某个节点入队超过n次，说明存在负环，无解
 *
*flag[], tag[]: 标记数组
l[]: 正向图邻接表
r[]: 反向图邻接表
dfs(): 从节点1可达的所有节点
dfs2(): 能够到达节点n的所有节点
 *
*只对在有效节点集合中的边构建约束
添加两种约束：
a[i] ≤ b[i] + 1 (即 b[i] - a[i] ≥ -1)
b[i] ≤ a[i] - 2 (即 a[i] - b[i] ≥ 2)
 *
 *
*使用SPFA检测是否存在负环
如果存在负环则无解，输出"No"
否则根据最短路距离计算每条边的权值并输出
 *
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1009, M = 5009;

int to[M<<1], nxt[M<<1], w[M<<1], head[N], cnt;
void add(const int x, const int y, const int z) {
    to[++cnt] = y; w[cnt] = z; nxt[cnt] = head[x]; head[x] = cnt;
}

bool vis[N];
int c[N], d[N], x, y, i, n;
bool spfa() {
    queue<int> q;
    for (q.push(1), vis[1] = c[1] = 1; !q.empty();) {
        for (x = q.front(), q.pop(), vis[x] = false, i = head[x]; i; i = nxt[i]) {
            if (d[(y=to[i])] < w[i] + d[x]) {
                d[y] = d[x] + w[i];
                if (!vis[y]) {
                    q.push(y), vis[y] = true;
                    if (++c[y] > n) return true;
                }
            }
        }
    }
    return false;
}

bool flag[N], tag[N];
vector<int> l[N], r[N];
void dfs(const int t) {
    int j;
    for (flag[t] = true, j = 0; j < l[t].size(); ++j)
        if (!flag[l[t][j]]) dfs(l[t][j]);
}

void dfs2(const int t) {
    int j;
    for (tag[t] = true, j = 0; j < r[t].size(); ++j)
        if (!tag[r[t][j]]) dfs2(r[t][j]);
}

int main() {
    fast;
    int m, a[M], b[M];
    for (cin >> n >> m, i = 1; i <= m; ++i) cin >> a[i] >> b[i];
    for (i = 1; i <= m; ++i) l[a[i]].push_back(b[i]), r[b[i]].push_back(a[i]);
    for (dfs(1), dfs2(n), i = 1; i <= n; ++i) flag[i] &= tag[i];//节点i既从节点1可达又能到达节点n时
    for (i = 1; i <= m; ++i) if (flag[a[i]] && flag[b[i]]) {
        add(a[i], b[i], 1); add(b[i], a[i], -2);
    }
    if (spfa()) cout << "No\n";
    else {
        for (cout << "Yes\n", i = 1; i <= m; ++i) {
            if (flag[a[i]] && flag[b[i]]) cout << d[b[i]] - d[a[i]] << '\n';
            else cout << "1\n";
        }
    }
    return 0;
}