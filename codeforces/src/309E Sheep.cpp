//
// Created by Psy.C on 2026/1/3.
//
/**
 *
* 当 j < i 时：
没有可用位置（空区间）
可用位置数应该是 0
所以条件变成 if (b[j] > 0) return false
这意味着：如果在无效区间内有需要安排的元素，就返回false
只对有意义的区间（j ≥ i）起作用，对无效区间（j < i）自动满足约束条件
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
#define inf 0x3f3f3f3f
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

template<typename T, typename V>
void minn(T& x, V y) { if (x > y) x = y; }

int vis[N], n, pos[N], l[N], r[N], ans[N];
bool ok(const int mid) {
    memset(vis, 0, sizeof vis);
    rep(i,n) pos[i] = n;
    rep(i,n) {
        int b[N] = {};
        rep(j,n) if (!vis[j]) b[pos[j]]++;//未访问元素在pos位置的计数
        rep(j,n) b[j] += b[j - 1];//位置≤j的元素总数
        rep(j,n) if (b[j] > max(j - i + 1, 0)) return false;//检查约束
        int nw = 0, nd = n;
        for (int j = n; j >= i; --j) if (b[j] == j - i + 1) nd = j;
        rep(j,n) if (!vis[j] && r[j] < r[nw] && pos[j] <= nd) nw = j;//未访问、r值最小、满足位置约束的元素
        ans[i] = nw; vis[nw] = 1;//第i个位置的安排结果
        rep(j,n) if (!vis[j] && max(l[j], l[nw]) <= min(r[j], r[nw])) {
            minn(pos[j], i + mid);//更新相交区间的pos值 最早可安排位置
        }
    }
    return true;
}

int main() {
    fast;
    cin >> n; r[0] = inf;
    rep(i,n) cin >> l[i] >> r[i];
    int L = 0, R = n - 1, p = 0;
    while (L <= R) {
        const int mid = (L + R) >> 1;
        if (ok(mid)) p = mid, R = mid - 1; else L = mid + 1;
    }
    ok(p);
    rep(i,n) cout << ans[i] << " \n"[i==n];
    return 0;
}