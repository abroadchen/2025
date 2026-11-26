//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
node：每个任务含 a（某种量）、b（每步增量）、d（当前比率 a/b）。
operator< 定义为 d 大者优先——配合 priority_queue 为大顶堆按 d 排序
若某任务 p.d - i < -1，即处理时它的剩余不足（时间已不够），返回失败。
否则更新 p.d += x*1.0/p.b，表示该任务消耗了 x 后在 d 上增加 x/b，放回堆。
k 步全部成功则返回 1
读入 a、b，计算初始 d = a/b（用浮点保留精度）。
r 初始为 inf（2e12）。
二分：若 check(mid) 可行，说明 mid 可行，收窄右边界找更小值；否则左移。
最终 ans 为最小可行 x；没有可行则保持 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define int long long
using namespace std;

constexpr int N = 2e5+5, inf = 2e12;

struct node { int a, b; double d; } a[N];
bool operator<(const node &x, const node &y) { return x.d > y.d; }

int n, k;
bool check(int x) {
    priority_queue<node> q;
    rep(i,n) q.push(a[i]);
    rep(i,k) {
        auto p = q.top(); q.pop();
        if (p.d-i < -1) return 0;
        p.d += x*1.0/p.b; q.push(p);
    }
    return 1;
}

int l, r = inf, ans = -1;
signed main() {
    fast;
    cin >> n >> k;
    rep(i,n) cin >> a[i].a;
    rep(i,n) {
        cin >> a[i].b;
        a[i].d = a[i].a*1.0/a[i].b;
    }
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans;
    return 0;
}