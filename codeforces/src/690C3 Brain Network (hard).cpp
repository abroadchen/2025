//
// Created by Psy.C on 2026/4/16.
//
/**
fa[i][j]表示节点i向上跳2^j步到达的祖先节点

确保u的深度不小于v的深度
第一个循环：将u提升到与v相同深度的位置
for (int i = 18; ~i; i--)：从大到小遍历2的幂次（~i表示i>=0）
if (dep[fa[u][i]] >= dep[v])：如果向上跳2^i步不会超过v的深度
u = fa[u][i];：将u向上跳2^i步
if (u == v) return u;：如果u和v重合，说明v是u的祖先
第二个循环：同时向上跳跃，直到找到最近公共祖先
return fa[u][0];：返回最近公共祖先
计算节点u和v之间的距离
距离 = dep[u] + dep[v] - 2*dep[lca(u,v)]
即：u的深度 + v的深度 - 2*最近公共祖先的深度

将节点1和2的所有祖先都设置为节点1（因为节点2的父亲是节点1）
设置dep[1]=0（根节点深度为0），dep[2]=1
输出"1 "（前两个节点间的距离是1）
a = 1, b = 2：a和b维护当前树的直径的两个端点
cin >> p;：读入当前节点i的父亲节点p
fa[i][0] = p;：设置i的直接父亲为p
dep[i] = dep[p] + 1;：设置i的深度为父亲深度+1
更新倍增数组：fa[i][j] = fa[fa[i][j-1]][j-1]
表示从i开始先跳2^(j-1)步到达中间节点，再从中间节点跳2^(j-1)步
这样就完成了从i跳2^j步的操作
如果新节点i到a的距离大于当前直径长度，更新b=i
否则如果新节点i到b的距离大于当前直径长度，更新a=i
这样始终保持a和b是当前已构建部分的直径两端点
输出当前树的直径（即a和b之间的距离）

时间复杂度为O(n log n)，其中log n来自LCA查询
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int dep[N], fa[N][20];
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 18; ~i; i--)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 18; ~i; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int get(int u, int v) {
    return dep[u] + dep[v] - 2*dep[lca(u, v)];
}

int n, x;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 0; i <= 18; ++i) fa[1][i] = fa[2][i] = 1;
    dep[1] = 0; dep[2] = 1;
    cout << "1 ";
    for (int i = 3, p, a = 1, b = 2; i <= n; ++i) {
        cin >> p; fa[i][0] = p; dep[i] = dep[p] + 1;
        for (int j = 1; j <= 18; ++j)
            fa[i][j] = fa[fa[i][j-1]][j-1];
        if (get(i, a) > get(a, b)) b = i;
        else if (get(i, b) > get(a, b)) a = i;
        cout << get(a, b) << ' ';
    }
    return 0;
}