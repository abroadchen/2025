//
// Created by Psy.C on 2026/4/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int fa[N];
int find(int x) {
    int t = x;
    while (fa[x] != x) x = fa[x];//找到根节点
    while (fa[t] != t) {//将路径上的所有节点直接连接到根节点
        int c = t;
        t = fa[t];
        fa[c] = x;
    }
    return x;
}
priority_queue<int, vector<int>, less<>> q[N];//最大堆
int n, m, num[N];//n为节点数，m为边数，num存储每个节点的值
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i];
        fa[i] = i;
    }
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        int fau = find(u), fav = find(v);
        fa[fau] = fav;//合并两个连通分量
    }
    for (int i = 1; i <= n; ++i)
        q[find(i)].push(num[i]);//将其值放入所属连通分量的最大堆中
    for (int i = 1; i <= n; ++i) {
        int pos = find(i);//节点i所属的连通分量
        num[i] = q[pos].top();//该连通分量中最大的值分配给节点i
        q[pos].pop();//从堆中移除已分配的值
    }
    for (int i = 1; i <= n; ++i)
        //第一个数字前面不加空格，后续数字前加空格
        printf("%s%d", i==1 ? "" : " ", num[i]);
    printf("\n");
    return 0;
}