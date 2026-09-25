//
// Created by Psy.C on 2026/9/24.
//
/**
读 n、k，求所有 a[i] 的和 S
R 是枚举步长 r 的上界：r 最多不会超过 S+k（越大越不可能满足条件，所以取这个上限
对每个 l，R/(R/l) 给出使 R/l（向下取整）值相同的最大 r，从而把 [1, R] 分成若干"商相同"的段。
这样只需对每段取代表 r（通常是段的最大端点 r）计算一次判定，复杂度降为 O(√R)
(a[i]-1)/r：把 a[i] 中的元素按块大小 r 分组。
(a[i]-1)/r * r：是把 a[i] 向上取整到 r 的倍数所需的量（补齐到下一个整块）某种形式。
n*r - S：把所有元素补足到每个"块首"之间的基础量。
总 sum 表示把 n 个元素按步长 r 排列、补齐到整块所需的总容量。
直观理解：每个元素 a[i] 占据若干连续块，为了"够放"需要把整体拉长到某些 r 的倍数，sum 就是这种拉长的总量（成本
若该步长 r 所需的总容量 ≤ k（预算内可行）。
因为整除分块从 l=1 往大枚举，r 单调增大，所以不断用更大的可行 r 覆盖 ans，最终 ans 就是满足条件时能取到的最大 r（最后一个可行段的 r）
输出最大可行步长 r
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a[105], n, k, S, ans;
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i], S += a[i];
    int R = S + k;
    for (int l = 1, r; l <= R; l = r + 1) {
        r = R/(R/l);
        int sum = n*r-S;
        for (int i = 1; i <= n; ++i) sum += (a[i]-1)/r*r;
        if (sum <= k) ans = r;
    }
    cout << ans;
    return 0;
}