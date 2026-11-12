//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
n：元素个数；g[]：元素值；lim：每段和上限；m：允许的最大段数
g[1..n] 是待处理的权值序列。
输入 x：表示从下标 x 开始往后分段。
逻辑：贪心地把元素尽量塞进当前段，一旦累加 v+g[i] 超过 lim 就新开一段。
统计出从 x 到 n 至少需要几段 cnt。
返回 cnt > m：是否需要的段数超过了允许的段数 m
二分找最大的起始下标 x，使得从 x 开始贪心分段所需段数仍超过 m。
check 返回真（段数 > m）→ 说明 x 起点太靠后、段数吃不消，只能把 l 上移；否则 r 下移。
最终答案输出 n - l
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

int n, g[N], lim, m;
inline bool check(int x) {
    int cnt = 1, v = 0;
    for (int i = x; i <= n; i++) {
        if (v+g[i] > lim) { cnt++; v = g[i]; }
        else v += g[i];
    }
    return cnt > m;
}

int l, r, mid;
int main() {
    fast;
    cin >> n >> m >> lim;
    for (int i = 1; i <= n; i++) cin >> g[i];
    l = 0, r = n;
    while (l < r) {
        mid = (l+r+1)>>1;
        if (check(mid)) l = mid; else r = mid-1;
    }
    cout << n-l;
    return 0;
}