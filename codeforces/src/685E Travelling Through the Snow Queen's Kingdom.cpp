//
// Created by Psy.C on 2026/4/15.
//
/**
l, r：查询的时间范围 [l, r]（包含l和r时刻）
s, t：查询的起终点
id：查询的原始编号
重载<运算符：按左端点降序排序
n：节点数
m：边的数量（时间序列）
k：查询数
u[i], v[i]：第i条边的两个端点
f[i][j]：节点i和j之间的最新连通时间
ans[i]：第i个查询的答案

读入图的边：每条边表示在特定时间连接两个节点
读入查询：时间范围和查询的起终点
排序：按查询开始时间降序排列
初始化f数组：用极大值表示初始时不连通
倒序遍历：从时间m到1，这样可以维护最新的连通性信息
更新边权：设置当前边的连通时间
Floyd更新：通过当前边更新所有相关的最短路径
处理查询：检查当前时间范围内是否存在连通路径

倒序处理：从最后时刻向前处理，维护任意两点间的最新连通时间
动态更新：每加入一条边，就更新通过这条边可能改善的所有连通性
查询判断：对于查询[l,r,s,t]，如果s和t的最新连通时间≤r，则在时间段内连通
特殊情况：同一点总是连通的（s==t）
时间复杂度约为O(m*n²+k)，适用于节点数不太大的情况

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 3e6+5, M = 3e5+5, K = 2005;
struct node {
    int l, r, s, t, id;
    bool operator<(const node &o) const {
        return l > o.l;
    }
} q[N];

int n, m, k, u[M], v[M], f[K][K], ans[N];
signed main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) cin >> u[i] >> v[i];
    for (int i = 1; i <= k; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].s >> q[i].t;
        q[i].id = i;
    }
    sort(q + 1, q + k + 1);
    memset(f, 0x3f3f, sizeof f);
    int cnt = 1;
    for (int i = m; i >= 1; --i) {
        f[u[i]][v[i]] = f[v[i]][u[i]] = i;
        for (int j = 1; j <= n; ++j)
            f[u[i]][j] = f[v[i]][j] = min(f[v[i]][j], f[u[i]][j]);
        while (cnt <= k && q[cnt].l == i) {
            if (f[q[cnt].s][q[cnt].t] <= q[cnt].r || q[cnt].s == q[cnt].t)
                ans[q[cnt].id] = 1;
            ++cnt;
        }
    }
    for (int i = 1; i <= k; ++i)
        cout << (ans[i] == 1 ? "Yes" : "No") << '\n';
    return 0;
}