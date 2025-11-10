//
// Created by Psy.C on 2025/11/10.
//
/*
 *a存储输入数据，二维数组ans用于动态规划缓存
 *
 *当k=0时，返回n本身
 *如果n小于限制值，直接从预计算的数组中返回结果
 *
 *ans[0][i] = i（基础情况）
 *
 *在给定集合a[0..k-1]中，不超过n且不能被任何a[i]整除的正整数个数
 *总数减去能被至少一个数整除的数的个数
 *
 *
 *不超过 j 且能被 a[i-1] 整除的正整数个数
*ans[i-1][j]：不考虑第i-1个因子时的结果
ans[i-1][j/a[i-1]]：需要排除的能被a[i-1]整除的数的个数
两者相减得到考虑第i-1个因子后的正确计数

i-1 本质上是表示在动态规划过程中的"前一个状态"
左边：ans[i][j]
表示不超过 j 且不能被前 i 个数（a[0] 到 a[i-1]）整除的数的个数
右边分解：
ans[i-1][j]：
表示不超过 j 且不能被前 i-1 个数（a[0] 到 a[i-2]）整除的数的个数
ans[i-1][j/a[i-1]]：
表示不超过 j/a[i-1] 且不能被前 i-1 个数整除的数的个数
这实际上等于：不超过 j 且能被 a[i-1] 整除但不能被 a[0] 到 a[i-2] 整除的数的个数


 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 105, inf = 1e5;
int a[N], ans[N][inf];

ll dfs(ll n, int k) {
    if (k == 0) return n;
    if (n < inf) return ans[k][n];
    return dfs(n, k-1) - dfs(n/a[k-1], k-1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n; int k; cin >> n >> k;
    for (int i = 0; i < k; ++i) cin >> a[i];
    sort(a, a + k);//对数组a进行升序排序
    for (int i = 0; i < inf; ++i) ans[0][i] = i;
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < inf; ++j)
            ans[i][j] = ans[i-1][j] - ans[i-1][j/a[i-1]];
    }
    cout << dfs(n, k) << '\n';
    return 0;
}