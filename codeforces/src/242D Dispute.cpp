//
// Created by Psy.C on 2025/12/15.
//
/*
*n：图中节点的总数
m：图中边的总数
*e[N]：邻接表数组，e[i]是一个vector，存储与节点i相邻的所有节点
ans：vector容器，用于存储按顺序激活的节点序列
 *v1, v2：边的两个端点
*a[N]：数组，存储每个节点的激活阈值（需要多少个邻居被激活才能自己被激活）
d[N]：数组，存储每个节点当前有多少个邻居已经被激活，初始化为0
 *
 *q，用于BFS算法处理节点激活顺序
*遍历所有节点（从1到n）
如果节点i的激活阈值为0（即不需要任何邻居激活就能自己激活）
将该节点加入队列q和答案序列ans中
 *
*当队列不为空时继续处理
取出队首节点u（已被激活的节点）
将节点u从队列中弹出
*遍历节点u的所有邻居节点v（使用C++11的范围for循环）
将邻居节点v的激活计数d[v]加1（因为u已经被激活）
如果邻居节点v的激活计数等于其激活阈值a[v]：
将节点v加入队列q（v现在可以被激活了）
将节点v加入答案序列ans（记录激活顺序）
 *
 *输出被激活节点的总数
*遍历答案序列ans中的所有节点
输出每个节点编号，节点之间用空格分隔，最后一个节点后换行
 *
*时间复杂度：O(n + m)
空间复杂度：O(n + m)
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<int> e[N], ans;
    for (int i = 0, v1, v2; i < m; ++i) {
        cin >> v1 >> v2;
        e[v1].push_back(v2); e[v2].push_back(v1);
    }
    int a[N], d[N]={};
    queue<int> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) if (a[i] == 0) {
        q.push(i); ans.push_back(i);
    }
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (int v : e[u]) {
            d[v]++;
            if (d[v] == a[v]) {
                q.push(v);
                ans.push_back(v);
            }
        }
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}