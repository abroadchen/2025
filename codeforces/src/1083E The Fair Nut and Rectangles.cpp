//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
决策 j 为前驱，i 为后继时：d[i] = max(d[j] + (a[i].x−a[j].x)·a[i].y − a[i].v)。
这只保留了"j 项"线性部分 d[j] − a[j].x·a[i].y（其余 a[i].x·a[i].y − a[i].v 对所有 j 相同）
返回点 (a[i].x, d[i]) 与 (a[j].x, d[j]) 连线斜率，用于凸壳维护（判断某决策点是否会被丢弃）
① 队首弹出：因为查询的直线斜率 a[i].y 单调变化，队首不再最优时直接弹出——这是"决策单调性 + 双端队列"的经典滑窗式维护。
② 队尾插入：新决策 i 加入前，不断弹出队尾维持队列中[决策点连线的斜率单调递减（上凸壳）]性质；用 f2（相邻点连线斜率）判断。
整体是 O(n) 时间（每个点进出队各一次）的斜率优化 DP。前提是"斜率 a[i].y 单调 + 横坐标 a[i].x 单调"（已由排序保证）

如果后一段斜率 f2(i,q[r]) 大于前一段斜率 f2(q[r],q[r-1])（即 f2(q[r],q[r-1]) < f2(i,q[r])），说明三个点 q[r-1] → q[r] → i 的斜率不再单调递减/递增，即凸性被破坏**,此时 q[r] 落在凸包内部、成了被中间"覆盖"的拐点，永远不会贡献最优解，所以直接从队尾 r-- 移除，然后继续检查新的队尾，直到保持凸壳斜率单调为止
队首 (l++)：处理"斜率随查询单调变化"时旧决策被新决策超越，属于出队（淘汰旧优）‍；
队尾 (r--)：负责维护决策点集合的凸性，保证整个队列始终是一个"斜率单调"的凸壳，这样队首弹出才能严格成立**
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 1e6+5;

struct node {
    ll x, y, v;
    bool operator<(const node &o) const { return x < o.x; }
} a[N];

ll d[N];
ll f1(int i, int j) { return d[i]+(a[j].x-a[i].x)*a[j].y-a[j].v; }
double f2(int i, int j) { return 1.0*(d[i]-d[j])/(a[i].x-a[j].x); }

int l, r, q[N];
ll ans;
int main() {
    fast;
    int n; cin >> n;
    rep(i,n) cin >> a[i].x >> a[i].y >> a[i].v;
    sort(a+1, a+1+n);
    rep(i,n) {
        while (l < r && f1(q[l],i) < f1(q[l+1],i)) l++;//队首不再更优，出队
        d[i] = f1(q[l],i), ans = max(ans, d[i]);//取队首为最优前驱
        while (l < r && f2(q[r],q[r-1]) < f2(i,q[r])) r--;//不符合凸性，弹尾
        q[++r] = i;
    }
    cout << ans << '\n';
    return 0;
}