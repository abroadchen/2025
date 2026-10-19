//
// Created by Psy.C on 2026/10/18.
//
/**
l=DFS序/d=发现时间, r=该SCC的代表(收缩后), d=访问标记
e=原图邻接表, s=该SCC的成员集合
已访问：返回该点收缩后的代表或发现时间
标记访问、入栈、赋发现时间
DFS，lowlink 取 min
x 是 SCC 根（low==dfn）
弹出栈内成员
归入以 x 为代表的 SCC
合并出边
这里判断的是 v[i].r != x，即该 SCC 是否有出边指向其他 SCC（不是入度）。若 !b 表示该 SCC 没有指向其他 SCC 的出边（即它是 DAG 上的汇点）。所以 ans 记录的是"出度为 0 且成员最少"的 SCC。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct node {
    int l, r, d;
    vector<int> e, s;
} v[N];

int n, t, ans;
vector<int> s;
int get(int x) {
    if (v[x].d) return v[x].r ? n : v[x].l;
    s.push_back(x); v[x].d = v[x].l = ++t;
    for (int i : v[x].e) v[x].l = min(v[x].l, get(i));
    if (v[x].l == v[x].d) {
        for (int y = 0; y != x; s.pop_back()) {
            y = s.back();
            v[y].r = x; v[x].s.push_back(y);
            if (x != y) v[x].e.insert(v[x].e.end(), v[y].e.begin(), v[y].e.end());
        }
        bool b = 0;
        for (int i : v[x].e) b |= v[i].r != x;//判断该 SCC 是否有"指向别的 SCC"的出边
        (!b && (!ans || v[x].s.size() < v[ans].s.size())) && ((ans=x));//取成员数最少的那个记录为 ans
    }
    return v[x].l;
}

int m, h, a[N];
int main() {
    fast;
    cin >> n >> m >> h;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        if ((a[x]+1)%h == a[y]) v[x].e.push_back(y);//x→y 边（规则1）
        if ((a[y]+1)%h == a[x]) v[y].e.push_back(x);//y→x 边（规则2）
    }
    for (int i = 1; i <= n; ++i) get(i);//对所有点跑 Tarjan
    cout << v[ans].s.size() << '\n';
    for (int i : v[ans].s) cout << i << ' ';//// 输出该 SCC 成员
    return 0;
}