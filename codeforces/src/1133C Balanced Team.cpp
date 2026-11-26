//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
i 是窗口左端点（最小值），j 是右端点（最大值）。
while 条件 a[j] <= a[i]+5：不断扩展右端点直到 a[j] - a[i] > 5，即差值超过 5 停止。
每次扩展时更新 res = max(res, j-i+1)（当前区间长度）。
由于序列已排序且 i 递增，j 单调不减 → 双指针 O(n)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e5+5;
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
int n, a[N], res;
int main() {
    fast;
    read(n);
    rep(i,n) read(a[i]);
    sort(a+1,a+n+1);
    int j = 1;
    rep(i,n) {
        while (j <= n && a[j] <= a[i]+5) {
            res = max(res,j-i+1);
            ++j;
        }
    }
    cout << res;
    return 0;
}