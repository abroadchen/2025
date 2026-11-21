//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
node {a,b,w}：一条边，两端点 a、b，权值 w。
find：并查集路径压缩查找 fa[i] = i，初始化所有点的父节点。
读 m 条边存入 v。
k=1，先用 ranges::sort(v, cmp) 按权值升序排序。
若 m>0，第一组的首条边加入 v1[1]。
遍历每条边：若当前权值与上一条不同就 k++（新开一组），把边放入对应权值组 v1[k]。
最终 v1[1..k] 中每组存的是权值相同的一批边。注意这里 rep(i,m) 从 i=1 到 m，访问 v[i-1]——i=1 时访问 v[0]，合理（已预先压入首边，但会重复压入一次 v[0]，略有冗余但不影响正确性）。实际首边被压入两次（一次在 if 里，一次在循环里）——属于小瑕疵，不影响结果
对每一组权值相同的边 v1[i]（i 从 0 到 k）：

提前终止：if (x >= n-1) break——已合并 n-1 条边（MST 完成），停止。
第一遍扫描（只统计不合并）‍：对组内每条边，若两端尚未连通（fa[find(j.a)] != fa[find(j.b)]），ans++。
这一步统计的是"在当前并查集状态下，本权值组里有多少条边是可选/有效的（即两端未连通、本可加入）"。
第二遍扫描（真正合并）‍：再次遍历组内边，若两端仍未连通则执行并查集合并，x++（记录已选边数）。
这就是克鲁斯卡尔算法按权值从小到大合并的常规操作。
两步分开的原因：在同一权值组内，若一条边能使两端连通而另一条同类权值边也能连通不同端点，它们之间形成"可替换"关系。先统计可能加入的边数（ans），再实际合并，从而算出"最大可加入的本组边数"
输出 ans - n + 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5, M = 1e6+5;

struct node { int a, b, w; };
bool cmp(node x, node y) { return x.w < y.w; }

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, m, a, b, c, k, ans, x;
vector<node> v, v1[N];
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n+20; i++) fa[i] = i;
    rep(i,m) {
        cin >> a >> b >> c; v.push_back({a,b,c});
    }
    k = 1; ranges::sort(v, cmp);
    if (m > 0) v1[k].push_back({v[0].a, v[0].b, v[0].w});
    rep(i,m) {
        if (v[i].w != v[i-1].w) k++;
        v1[k].push_back({v[i].a, v[i].b, v[i].w});
    }
    for (int i = 0; i <= k; i++) {
        if (x >= n-1) break;
        for (auto &j : v1[i]) if (fa[find(j.a)] != fa[find(j.b)]) ans++;
        for (auto &j : v1[i])
            if (fa[find(j.a)] != fa[find(j.b)])
                fa[find(j.a)] = find(j.b), x++;
    }
    cout << ans-n+1 << '\n';
}

signed main() {
    fast;
    solve();
    return 0;
}