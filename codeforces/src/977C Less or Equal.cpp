//
// Created by Psy.C on 2026/10/22.
//
/**
memset(a, 128, sizeof(a))：将数组初始化为一个很大的负数（0x80808080 当作 int 是一个很大的负数，- 后）。这里是为了后续边界而设。
读入 n 个元素后 sort(a+1, a+n+1) 升序排序
若 k = 0，要求数组中没有 <= x 的元素，即 x < a[1]（最小元素）。
a[1] == 1 时无法取到小于 1 的正整数 x（题目 x ≥ 1），输出 -1；否则输出 a[1]-1
排序后，a[k] 是第 k 小的元素。
若想要"恰好 k 个元素 <= x"，可行的 x 范围是 [a[k], a[k+1]-1]。
冲突判断 if (a[k+1] == a[k])：若第 k+1 个元素和第 k 个相同，则任何 x 都让小于等于它的元素要么只有 k 个要么有 k+1 个（因为相等元素必须同时计入），无法恰好 k 个 → 输出 -1。
否则取 x = a[k]（最便宜的下界），但要保证 x <= inf（1e9 的上限约束）：若 a[k] <= inf 输出 a[k]，否则输出 inf
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e6+5, inf = 1e9;

int n, k, a[N];
int main() {
    fast;
    cin >> n >> k;
    memset(a, 128, sizeof(a));
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    if (k == 0) {
        if (a[1] == 1) cout << -1;
        else cout << a[1]-1;
        return 0;
    }
    if (a[k+1] == a[k]) { cout << -1; return 0; }
    if (a[k] <= inf) cout << a[k];
    else cout << inf;
    return 0;
}