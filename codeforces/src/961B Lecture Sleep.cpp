//
// Created by Psy.C on 2026/10/21.
//
/**
窗口左右端点 [x, y]，初始 x=1, y=k。
每轮：先记录当前 cnt 是否刷新最大值，记录最优窗口 [l, r]。
然后窗口右移一格：若 t[x]==0 说明从左端滑出的那个"待打开"数要减掉；y 右移后若 t[y]==0 说明新进入窗口的"待打开"数要加上。
循环条件 x <= n-k+1，保证窗口不越界。
可确证：这是标准的固定长度 k 的滑动窗口，cnt 始终 = 当前窗口内 t[i]==0 的 a[i] 之和；并记录使 cnt 最大的窗口位置 [l,r] 及最大值 mx
对所有位置 i 遍历：
若 i 在最优窗口 [l,r] 内且 t[i]==0，跳过（这些正是窗口内"被打开的"，其贡献已经通过 mx（即窗口内 cnt）计入）。
否则累加 a[i]*t[i]，即 t[i]==1 的数贡献生效，t[i]==0 且不在窗口内的数为 0

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e5+5;

int n, k, a[N], t[N], cnt;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> t[i];
    rep(i,k) if (t[i] == 0) cnt += a[i];
    int x = 1, y = k, mx = 0, l = 0, r = 0;
    while (x <= n-k+1) {
        if (cnt > mx) { mx = cnt; l = x; r = y; }
        if (t[x] == 0) cnt -= a[x];
        x++; y++;
        if (t[y] == 0) cnt += a[y];
    }
    rep(i,n) {
        if (i >= l && i <= r && t[i] == 0) continue;
        mx += a[i]*t[i];
    }
    cout << mx;
    return 0;
}