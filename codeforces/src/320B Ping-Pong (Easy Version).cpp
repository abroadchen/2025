//
// Created by Psy.C on 2026/1/7.
//
/**
* n：当前处理的区间数量
a[N]：存储区间的左端点
b[N]：存储区间的右端点
f[N]：访问标记数组，用于DFS
 *
*DFS函数：标记节点i为已访问
遍历所有未访问的节点
如果区间i的左端点在区间k内部，或者区间i的右端点在区间k内部，则继续DFS
 *
*m == 1：添加新区间
m == 2：查询两个区间是否连通
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 111
using namespace std;

int n, a[N], b[N];
bool f[N];
void dfs(const int i) {
    f[i] = true;
    for (int k = 1; k <= n; ++k) {
        if (f[k]) continue;
        if (a[i] > a[k] && a[i] < b[k]) dfs(k);
        else if (b[i] > a[k] && b[i] < b[k]) dfs(k);
    }
}


int main() {
    fast;
    int k; cin >> k;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= k; ++i) {
        int m; cin >> m;
        if (m == 1) {
            n++;
            cin >> a[n] >> b[n];
        }
        if (m == 2) {
            int x, y; cin >> x >> y;
            memset(f, 0, sizeof(f));
            dfs(x);
            cout << (f[y] ? "YES\n" : "NO\n");
        }
    }
    return 0;
}