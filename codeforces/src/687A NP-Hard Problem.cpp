//
// Created by Psy.C on 2026/4/15.
//
/**
起点u，终点v，权重w，下一个边的索引nxt
head数组：每个节点的邻接表头指针
cnt：边的计数器
add函数：向邻接表添加边
cl数组：节点颜色（0表示未染色，1和2表示两种不同颜色）
遍历节点u的所有邻居v
如果邻居v和当前节点u颜色相同，则不是二分图
如果邻居v未染色，则染成与u不同的颜色（1变2，2变1，使用3-cl[u]）
递归检查邻居v
初始化head数组：全部设为-1，表示没有邻接边

遍历所有节点：对未染色的节点进行处理
孤立节点：如果节点没有邻接边，直接染色为1
连通分量：从每个未访问节点开始DFS，尝试二分图染色
失败判断：如果不能形成二分图，输出-1
统计：计算两种颜色的节点数量
输出格式：
第一行：颜色1的节点数量
第二行：颜色1的节点列表
第三行：颜色2的节点数量
第四行：颜色2的节点列表
时间复杂度：O(n+m)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
struct node { int u, v, w, nxt; } e[N];

int head[N], cnt;
void add(int u, int v) {
    e[cnt].v = v; e[cnt].w = 0; e[cnt].nxt = head[u]; head[u] = cnt++;
}

int cl[N];
bool dfs(int u) {
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (cl[v] == cl[u]) return false;
        if (!cl[v]) {
            cl[v] = 3 - cl[u];
            if (!dfs(v)) return false;
        }
    }
    return true;
}

int n, m;
int main() {
    fast;
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        if (cl[i] != 0) continue;
        if (head[i] == -1) { cl[i] = 1; continue; }
        cl[i] = 1;
        if (!dfs(i)) { cout << "-1\n"; return 0; }
    }
    int w = 0, b = 0;
    for (int i = 1; i <= n; ++i) {
        if (cl[i] == 1) w++;
        if (cl[i] == 2) b++;
    }
    cout << w << '\n';
    for (int i = 1; i <= n; ++i)
        if (cl[i] == 1) cout << i << ' ';
    cout << '\n';
    cout << b << '\n';
    for (int i = 1; i <= n; ++i)
        if (cl[i] == 2) cout << i << ' ';
    cout << '\n';
    return 0;
}