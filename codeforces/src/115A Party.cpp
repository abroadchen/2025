//
// Created by Psy.C on 2025/11/15.
//
/*
*N = 2050：最大节点数
n：实际节点数
in[N]：每个节点的入度（有多少个父节点）
dep[N]：每个节点的深度（距离根节点的层级）
v[N]：邻接表，v[i]存储节点i的所有子节点
 *
*循环读入每个节点的父节点信息：
i：当前节点编号（从1到n）
a：节点i的父节点编号
如果a == -1，说明节点i是根节点，不做处理
否则：
将节点i添加到节点a的子节点列表中：v[a].push_back(i)
节点i的入度加1：in[i]++
 *
*创建队列q用于BFS遍历
找到所有入度为0的节点（即根节点），将它们加入队列
在树结构中，应该只有一个根节点
*当队列不为空时循环：
取出队首节点u
将u从队列中弹出
*遍历节点u的所有子节点：
v[u][i]：u的第i个子节点
设置子节点的深度：dep[v[u][i]] = dep[u] + 1
将子节点加入队列，准备后续处理
这实际上是在进行BFS遍历，计算每个节点的深度
 *
 *遍历所有节点，找出最大的深度值
 *输出树的高度（最大深度+1，因为深度从0开始计数）
 *
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#define sz(x) ((int)(x).size())
using namespace std;

const int N = 2050;
int n, in[N], dep[N];
vector<int> v[N];

int main() {
    scanf("%d",&n);
    for (int i = 1, a; i <= n; ++i) {
        scanf("%d",&a);
        if (a == -1) ;
        else v[a].push_back(i), in[i]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < sz(v[u]); ++i) {
            dep[v[u][i]] = dep[u] + 1;
            q.push(v[u][i]);
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) mx = max(dep[i], mx);
    printf("%d\n", mx + 1);
    return 0;
}