//
// Created by Psy.C on 2026/10/22.
//
/**
n：数字个数；A、B：比率判定的两个参数。
a[N]：存这 n 个数（下标从 1 开始）。
ans：当前剩余元素的总和，读入时累加 = 所有元素之和
若只有 0 或 1 个数，无法删除其他元素（要保留 a[1]），直接输出 0 结束
对 a[2..n]（即除 a[1] 外的所有元素）按升序排序。
注意：不包括 a[1]——a[1] 是被保留的元素。
升序排序后，a[n] 是最大的，a[2] 是最小的，这样后面从 i=n 往前删就能从大到小依次删除
检查删之前：a[1]*A / ans（整数除法）是否已 ≥ B。
若已达标，则不需要删任何数，直接输出 0
从 i=n（最大的元素）开始，往前删到 i=2。
每轮先 ans -= a[i]，把第 i 个元素从总和中去掉（即删除它）。
删除后检查 a[1]*A/ans >= B 是否满足：
若满足，输出 n-i+1 = 已经删除的元素个数（因为从 n 删到 i，删了 n-i 个，加上……实际是 n - i + 1 个，包含当前 i）。输出后 break 结束，不再继续删。
若一直删到最后 i=2 都没满足，循环正常结束，代码不输出任何东西（末尾无兜底输出，直接 return 0）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

int n, A, B, a[N], ans;
int main() {
    fast;
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) cin >> a[i], ans += a[i];
    if (n <= 1) { cout << "0\n"; return 0; }
    sort(a+2, a+n+1);
    if (a[1]*A/ans >= B) { cout << "0\n"; return 0; }
    for (int i = n; i > 1; i--) {
        ans -= a[i];
        if (a[1]*A/ans >= B) { cout << n-i+1; break; }
    }
    return 0;
}