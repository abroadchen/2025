//
// Created by Psy.C on 2026/3/26.
//
/**
y[N]：预计算的异或前缀数组，y[i] = 0^1^2^...^i
n, m：数组长度和询问数量
a[A]：输入数组
l[M], r[M]：每个询问的左右边界
ans[M]：每个询问的答案
t[A]：临时数组，存储当前计算的状态
y[i] 存储从0到i的所有整数的异或值：0^1^2^...^i
利用性质：0^1^2^...^i = (0^1^2^...^(i-1)) ^ i = y[i-1] ^ i
读入数组长度n和询问数m
读入数组a的元素
读入m个询问的区间[l[i], r[i]]

外层循环 (i从1到n)：

固定左端点i
内层循环1 (j从i到n)：

遍历以i为左端点的所有区间[i,j]
mn = min(a[i], a[j]), mx = max(a[i], a[j])：获取区间端点值的最小值和最大值
y[mx]^y[mn-1]：计算mn到mx之间所有整数的异或值
利用异或前缀性质：mn^(mn+1)^...^mx = (0^1^...^mx) ^ (0^1^...^(mn-1)) = y[mx]^y[mn-1]
t[j]的更新：
如果j==i（区间只有一个元素），t[j] = y[mx]^y[mn-1]
否则，t[j] = max(t[j-1], y[mx]^y[mn-1])，即当前最大异或值
内层循环2 (k从1到m)：

检查当前左端点i是否在第k个查询区间内
如果i >= l[k] && i <= r[k]，更新ans[k] = max(ans[k], t[r[k]])
时间复杂度：O(n² + nm) - 可能超时 空间复杂度：O(max(N,A,M))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, A = 50005, M = 5005;
int y[N], n, m, a[A], l[M], r[M], ans[M], t[A];
int main() {
    fast;
    y[0] = 0;
    for (int i = 1; i <= N-3; ++i) y[i] = y[i-1]^i;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> l[i] >> r[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int mn = min(a[i], a[j]), mx = max(a[i], a[j]);
            if (j == i) t[j] = y[mx]^y[mn-1];
            else t[j] = max(t[j-1], y[mx]^y[mn-1]);
        }
        for (int k = 1; k <= m; ++k) {
            if (i >= l[k] && i <= r[k])
                ans[k] = max(ans[k], t[r[k]]);
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}