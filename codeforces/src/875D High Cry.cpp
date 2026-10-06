//
// Created by Psy.C on 2026/10/6.
//
/**
st[l][i]：从 l 开始长度 2^i 的区间最大值。
b[l][i]：从 l 开始长度 2^i 的区间按位或结果。
递推：st[l][i] = max(st[l][i-1], st[l+2^(i-1)][i-1])，按位或同理。
从右往左 init 建表（for i=n..1），因为要用到后面的 st[min(...)]
r1(l,r)：O(1) 查询区间 [l,r] 的最大值。
r2(l,r)：O(1) 查询区间 [l,r] 的按位或。
两者都是标准的 Sparse Table 查询（取 L = floor(log2(len))，两段覆盖
左半部分二分：找最小的 a1（最左边起）使得区间 [mid, x-1] 的最大值 < a[x] 且区间 [mid, x] 的按位或 <= a[x]。
右半部分二分：找最大的 a2 使得区间 [x+1, mid] 的最大值 <= a[x] 且区间 [x, mid] 的按位或 <= a[x]。
最终 find(x) = (a2-x+1)*(x-a1+1)，即"以 x 为右/左两端点"的矩形面积
读入 n 和数组 a。
从右往左预处理 Sparse Table。
ans = n(n+1)/2：所有子区间的总数（C(n+1,2)，即所有 (l,r) 对）。
对每个位置 i 减去 find(i)。
输出剩余 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5, M = 23;

int st[N][M], a[N], b[N][M], n;
inline void init(int l) {
    st[l][0] = a[l], b[l][0] = a[l];
    for (int i = 1; i <= 20; ++i) {
        st[l][i] = max(st[l][i-1], st[min(l+(1<<(i-1)), n)][i-1]);
        b[l][i] = b[l][i-1]|b[min(l+(1<<(i-1)), n)][i-1];
    }
}
inline int r1(int l, int r) {
    int L = log(r-l+1)/log(2);
    return max(st[l][L], st[min(r-(1<<L)+1, n)][L]);
}
inline int r2(int l, int r) {
    int L = log(r-l+1)/log(2);
    return b[l][L]|b[min(r-(1<<L)+1, n)][L];
}

int find(int x) {
    int l = 1, r = x - 1, a1 = x, a2 = x;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (r1(mid, x-1) < a[x] && r2(mid, x) <= a[x])
            a1 = mid, r = mid - 1;
        else  l = mid + 1;
    }
    l = x + 1, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (r1(x+1, mid) <= a[x] && r2(x, mid) <= a[x])
            a2 = mid, l = mid + 1;
        else  r = mid - 1;
    }
    return (a2-x+1)*(x-a1+1);
}

signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i >= 1; --i) init(i);
    int ans = 1ll*n*(n+1ll)/2ll;
    for (int i = 1; i <= n; ++i) ans -= find(i);
    cout << ans << '\n';
    return 0;
}