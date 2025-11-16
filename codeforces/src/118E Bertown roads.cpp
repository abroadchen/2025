//
// Created by Psy.C on 2025/11/16.
//
/*
*n: 节点数
m: 边数
x, y: 临时变量，用于读取边的两个端点
cnt: 时间戳计数器
dfn[N]: 每个节点的DFS访问时间戳
low[N]: 每个节点能够追溯到的最早时间戳
e[N]: 邻接表，存储图的结构
ans: 存储结果边的定向
 *
 *当前节点x和父节点fa
 *为当前节点分配DFS时间戳，并初始化low值
 *遍历当前节点x的所有邻接节点y
 *如果节点y尚未被访问（是树边）
 *递归访问y，更新x的low值
 *将边(x,y)加入结果集（定向为x→y）
*如果low[y] > dfn[x]，说明边(x,y)是桥（割边）
如果存在桥，则无法构造边双连通定向，输出0并退出程序
 *如果节点y已被访问且不是父节点（是回边/前向边）
 *更新x的low值
 *如果y的访问时间早于x，说明是回边，将边加入结果集
 *
*树边：从父节点指向往子节点
回边：从后代指向祖先
 *
 *O(n + m)
 *
*Tree Edge (树边)
属于DFS生成树的边
当我们从当前顶点访问一个新的未访问顶点时形成的边
例如：如果我们从顶点A访问未访问的顶点B，则A→B是树边
 *
 *
*Back Edge (回边)
连接一个顶点到DFS树中其祖先节点的边
在有向图中形成环
在无向图中，指向父节点的边不被认为是回边
 *
* Forward Edge (前向边)
连接一个顶点到其后代节点的边，但不是树边
仅存在于有向图中
后代节点已经通过不同路径被访问过
例如：如果A→B是树边，同时还存在A→C，其中C是B的后代但在树中不直接相连
 *
*Cross Edge (交叉边)
连接既不是祖先也不是后代的顶点的边
连接不同的DFS树或分支中的顶点
仅存在于有向图中
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 3e5+10;
int n, m, x, y, cnt,
dfn[N], low[N];
vector<int> e[N];
vector<pair<int, int> > ans;

void dfs(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    for (int y : e[x]) {
        if (!dfn[y]) {
            dfs(y, x);
            low[x] = min(low[x], low[y]);
            ans.push_back({x, y});
            if (low[y] > dfn[x]) cout << "0\n", exit(0);
        } else if (y != fa) {
            low[x] = min(low[x], dfn[y]);
            if (dfn[y] < dfn[x]) ans.push_back({x, y});
        }
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (cin >> n >> m; m--;) {
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1, 0);//父节点设为0表示无父节点
    for (auto& i : ans) cout << i.first << " " << i.second << '\n';
    return 0;
}