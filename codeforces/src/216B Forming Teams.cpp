//
// Created by Psy.C on 2025/12/7.
//
/*
*a[N][N]：邻接矩阵，表示图的连接关系
cr[N]：冲突标记数组，标记有问题的节点
cl[N]：颜色数组，用于二分图着色（0或1表示两种颜色）
vis[N]：访问标记数组，记录节点是否已被访问
 *
*二分图检测：
s：当前节点
n：总节点数
c：当前节点的颜色（0或1）
将当前节点着色为c，并标记为已访问
遍历所有与当前节点相邻的节点：
如果邻接节点未访问，则递归访问并着相反颜色!c
如果邻接节点已访问，且颜色相同，则标记为冲突节点
 *
*统计冲突节点数量
由于每条冲突边被计算两次，所以除以2
如果剩余节点数是奇数，需要额外修正一个节点
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int a[N][N], cr[N], cl[N];
bool vis[N];

void dfs(const int s, const int n, const int c) {
    cl[s] = c; vis[s] = true;
    for (int i = 1; i <= n; ++i) {
        if (a[s][i] && !vis[i]) dfs(i, n, !c);
        else if (a[s][i] && vis[i]) {
            if (cl[s] == cl[i]) cr[i] = 1;
        }
    }
}

int main() {
    fast;
    int n, m; cin>>n>>m;
    memset(a, 0, sizeof(a));
    memset(vis, false, sizeof(vis));
    memset(cr, 0, sizeof(cr));
    memset(cl, 0, sizeof(cl));
    for (int i = 0, j, k; i < m; ++i) {
        cin >> j >> k;
        a[j][k] = a[k][j] = 1;//无向图的邻接矩阵
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, n, 0);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (cr[i]) cnt++;
    cnt /= 2;
    if ((n - cnt) % 2) cnt++;
    cout << cnt << '\n';
    return 0;
}