//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
d 是"阈值"（候选值），只考虑 a[i] <= d 的数；
x 是"目标数目"——问：取前 x 个这样的数，能否在总时间 ≤ tim 内完成；
s：累计"时间"；sum：当前段内 a[i] 之和（用于每 m 个时的一次性额外加时）；cnt：已取个数。
关键规则在 cnt % m == 0 那行：每累计 m 个，就把"这一段的 sum"整体再加一次到 s 并清零 sum，模拟一种"换行/换段额外代价"
b 是 a 的排序副本；
二分搜索 mid：候选阈值取 b[mid]（即排序后第 mid 个的值），问get(mid, b[mid])是否可行；
可行（返回真）→ 记录 ans=mid，尝试更大的 mid；
不可行 → 缩小。
最终：

ans=0 → 输出 0 1；
否则输出 ans 和 b[ans]（即能取的最大数量和此时的阈值）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

ll n, a[N], tim, m;
int get(ll x, ll d) {
    ll s = 0, cnt = 0, sum = 0;
    rep(i,n) {
        if (a[i] > d) continue;//超过阈值 d 的跳过
        cnt++; sum += a[i]; s += a[i];//记录个数、段内前缀和、总时间累加
        if (cnt == x) return s <= tim;//已凑够 x 个 → 判断时间是否够
        if (cnt && cnt%m == 0) { s += sum; sum = 0; }//每 m 个结算一次额外开销
        if (s > tim) return 0;//时间超了就失败
    }
    return 0;
}

ll b[N];
int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        cin >> n >> m >> tim;
        rep(i,n) cin >> a[i];
        rep(i,n) b[i] = a[i];
        sort(b+1, b+n+1);
        int l = 1, r = n, ans = 0;
        while (l <= r) {
            int mid = (l+r)>>1;
            if (get(mid, b[mid])) { l = mid+1; ans = mid; }
            else r = mid-1;
        }
        if (ans == 0) cout << "0 1\n";
        else cout << ans << ' ' << b[ans] << '\n';
    }
    return 0;
}