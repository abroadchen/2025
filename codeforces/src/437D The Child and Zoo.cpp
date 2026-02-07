//
// Created by Psy.C on 2026/2/7.
//

#include <algorithm>
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

struct node {//两个顶点v1、v2和边的权值val
    int v1, v2, val;
} e[N];

int fa[N];
int find(const int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    fast;
    int n, m, i; cin >> n >> m;
    int tot[N]{}, v[N];//每个连通分量的大小 每个节点的权值
    rep(i,n) { fa[i] = i; tot[i] = 1; }
    rep(i,n) cin >> v[i];
    rep(i,m) {
        cin >> e[i].v1 >> e[i].v2;
        e[i].val = min(v[e[i].v1], v[e[i].v2]);//两个端点权值的最小值
    }
    sort(e + 1, e + m + 1, [](const node a, const node b) {
        return a.val > b.val;
    });
    double sum = 0;
    rep(i,m) {
        const int x = find(e[i].v1), y = find(e[i].v2);
        if (x == y) continue;
        sum += 1. * e[i].val * tot[x] * tot[y];
        fa[y] = x;
        tot[x] += tot[y];//x的大小增加y的大小
        tot[y] = 1;//y的大小重置为1
    }
    cout << fixed << setprecision(6) << sum*2/(1.*n*(n-1)) << '\n';
    return 0;
}