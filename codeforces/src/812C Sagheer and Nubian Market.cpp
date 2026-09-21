//
// Created by Psy.C on 2026/9/21.
//
/**
n：物品个数；a[i]：第 i 个物品基础价值；S：预算上限。
b：临时数组，用于存放变换后的值
对每个 i，计算在"单价"为 x 时的价值 b[i] = a[i] + i*x。
排序，取最小的 x 个（贪心：买最便宜的）。
求和，若 <= S 则可行
[0, n] 间二分找最大的可行 x（仓库数/件数）。可行则记录 a1 = mid 并右移；不可行左移。结束后 a1 = 最大可购买数量
拿到最优数量 a1 后，重新计算选前 a1 个的最小总花费 a2，输出 a1 与 a2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e5+5;

int n, a[N], b[N], S;
bool check(int x) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) b[i] = a[i] + i*x;
    sort(b+1, b+n+1);
    for (int i = 1; i <= x; ++i) sum += b[i];
    return sum <= S;
}

int a1, a2;
signed main() {
    fast;
    cin >> n >> S;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int l = 0, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) { l = mid+1; a1 = mid; }
        else r = mid-1;
    }
    for (int i = 1; i <= n; ++i) b[i] = a[i] + i*a1;
    sort(b+1, b+n+1);
    for (int i = 1; i <= a1; ++i) a2 += b[i];
    cout << a1 << ' ' << a2;
    return 0;
}