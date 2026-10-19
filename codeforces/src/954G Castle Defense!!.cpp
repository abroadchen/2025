//
// Created by Psy.C on 2026/10/19.
//
/**
对最小高度 ans 做二分：check(ans) 判断是否能在 K 次操作内把所有元素抬到 ≥ ans。二分求出最大可达的"最小值"（即所有元素最终都≥X的X的最大值）
核心是贪心 + 差分：

从左到右扫描每个位置 i。当前位置 i 能影响它的操作是"起点在 [i-R, i] 的窗口"（即影响范围是 [i, i+R]）。
维护滑动窗口内当前累积的增量 t（= 基础值 a 的和 + 之前操作带来的额外增量 b 的和）。
若 t < ans，说明位置 i 不够高。此时只能在 i 位置开新操作（因为更靠左的操作已无法再影响 i），在 i 处补 ans-t 次操作，并把这次操作的贡献用差分数组 b 记录在窗口右端 i+R（表示从 i 到 i+R 都 +1）。
消耗操作次数 k；若 k<0 则失败。
滑动：移除左端 i-R 的基础值 a 和差分值 b，移入右端 i+1+R 的基础值。
这保证每次操作总是尽可能地靠左放置（最大化收益窗口），是经典的"覆盖区间加、最小化操作次数"贪心
为什么输出 l-1

二分里 check(m) 为真时 l=m+1，所以真正的最大高度是 l-1；若 l=0 说明 check(0) 都失败（不可能），实际输出 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
using namespace std;

constexpr ll N = 5e5+5, inf = 0x3f3f3f3f3f3f3f3f;

ll a[N], b[N], K, R, n;
bool check(ll ans) {
    memset(b, 0, sizeof b);
    ll k = K, t = 0;
    rep(i,R+1) t += a[i];//初始窗口 [0, R]
    rep(i,n) {
        if (t < ans) {//当前位置 i 达不到 ans
            k -= ans - t;//需要补 (ans-t) 次操作
            if (k < 0) return false;
            b[min(n-1, 1ll*(i+R))] += ans - t;//差分：在窗口右端 i+R 处记录补充量
            t = ans;//该位置被补到 ans
        }
        if (i >= R) t -= a[i-R] + b[i-R];//移出左端
        if (i + 1 + R < n) t += a[i+1+R];//移入右端
    }
    return true;
}


int main() {
    fast;
    cin >> n >> R >> K;
    rep(i,n) cin >> a[i];
    ll l = 0, r = inf, m;
    while (l < r) {
        m = (l+r)/2;
        if (check(m)) l = m+1;
        else r = m;
    }
    if (l == 0) cout << 0 << '\n'; else cout << l-1 << '\n';
    return 0;
}