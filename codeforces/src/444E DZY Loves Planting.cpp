//
// Created by Psy.C on 2026/2/8.
//
/**
x, y: 边的两个端点
w: 边的权重
siz[N]: 每个连通块的节点数量
sx[N]: 每个连通块的权值和
S: 所有权值的总和
pd: 标志位，表示是否找到了答案

条件 siz[fy] > S - sx[fy] 表示：一个连通块的节点数 > 另一个连通块的权值和
这意味着如果删除当前边，会形成一个节点多但权值小的块，和一个节点少但权值大的块

 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3005
using namespace std;

struct node {
    int x, y, w;
    bool operator<(const node a) const {
        return w < a.w;
    }
} a[N];

int fa[N];
int find(const int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int siz[N], sx[N], S;
bool pd;

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        fa[i] = i; siz[i] = 1;
        cin >> a[i].x >> a[i].y >> a[i].w;
    }
    fa[n] = n;
    for (int i = 1; i <= n; ++i) cin >> sx[i], S += sx[i];
    sort(a + 1, a + n);
    for (int i = 1; i < n; ++i) {
        const int fx = find(a[i].x), fy = find(a[i].y);
        if (fx == fy) continue;
        siz[fy] += siz[fx]; sx[fy] += sx[fx]; fa[fx] = fy;//合并两个连通块
        if (siz[fy] > S - sx[fy]) {//当前块大小 > 总权值 - 当前块权值
            cout << a[i].w; pd = true; break;
        }
    }
    if (!pd) cout << a[n-1].w;
    return 0;
}