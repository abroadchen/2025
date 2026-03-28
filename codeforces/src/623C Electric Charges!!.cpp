//
// Created by Psy.C on 2026/3/27.
//
/**
ans 存储最终答案
a[N] 存储坐标对
n 点的数量
mnl[i], mxl[i] 分别表示从左到第i个点y坐标的最小值和最大值
mnr[i], mxr[i] 分别表示从右到第i个点y坐标的最小值和最大值

检查给定误差e是否可行：

分别处理x坐标≤0和x坐标≥0的点
对于每个区间，计算包含这些点的矩形所需的最小平方和
使用前缀/后缀最值来优化y方向的范围计算
时间复杂度：O(n log(max_coord))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
#define inf 1e18
using namespace std;
constexpr int N = 1e5+5, inf1 = 1e9;

ll sqr(ll x) { return x * x; }

ll ans = inf;
ii a[N];
int n, mnl[N], mxl[N], mnr[N], mxr[N];
int check(ll e) {
    if (ans <= e) return 1;
    int now = 1;
    ll ans = inf;
    //处理x坐标 <= 0 的点
    for (int i = 1; i <= n; ++i) {
        if (a[i].first > 0) break;
        //找到距离a[i]不超过sqrt(e)的最远点
        while (now < n && sqr(a[now+1].first-a[i].first) <= e &&
            abs(a[now+1].first) <= abs(a[i].first)) ++now;
        while (abs(a[now].first) > abs(a[i].first)) --now;
        //y方向的范围约束
        int U = -inf1, D = inf1;
        if (i > 1) U = max(U, mxl[i-1]), D = min(D, mnl[i-1]);
        if (now < n) U = max(U, mxr[now+1]), D = min(D, mnr[now+1]);
        ans = min(ans, max(sqr(U-D), max(sqr(U), sqr(D))+
            max(sqr(a[i].first), sqr(a[now].first))));
    }
    //处理x坐标 >= 0 的点
    now = n;
    for (int i = n; i >= 1; --i) {
        if (a[i].first < 0) break;
        while (now > 1 && sqr(a[now-1].first-a[i].first) <= e &&
            abs(a[now-1].first) <= abs(a[i].first)) --now;
        while (abs(a[now].first) > abs(a[i].first)) ++now;
        int U = -inf1, D = inf1;
        if (i < n) U = max(U, mxr[i+1]), D = min(D, mnr[i+1]);
        if (now > 1) U = max(U, mxl[now-1]), D = min(D, mnl[now-1]);
        ans = min(ans, max(sqr(U-D), max(sqr(U), sqr(D))+
            max(sqr(a[i].first), sqr(a[now].first))));
    }
    return ans <= e;
}

#define mid ((l+r)>>1)
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    //前缀最值
    mnl[1] = mxl[1] = a[1].second;
    for (int i = 2; i <= n; ++i) {
        mnl[i] = min(mnl[i-1], a[i].second);
        mxl[i] = max(mxl[i-1], a[i].second);
    }
    //后缀最值
    mnr[n] = mxr[n] = a[n].second;
    for (int i = n-1; i >= 1; --i) {
        mnr[i] = min(mnr[i+1], a[i].second);
        mxr[i] = max(mxr[i+1], a[i].second);
    }
    ll l = 0, r = min(sqr(mnl[n]-mxl[n]), sqr(a[1].first-a[n].first));
    ans = r;
    while (l <= r) {
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}