//
// Created by Psy.C on 2026/2/26.
//
/**
g[l][r]表示范围[l,r]内有效分区的数量

遍历从2到n的所有可能段长度
对于每个段[l, r]：
将g[l][r]初始化为g[l+1][r]（即l不作为新子数组开头的情况）
尝试段内的所有可能分割点k
如果a[l] < a[k+1]（保持所需排序），通过乘积更新计数：
[l, k]段的分区方式数量：get(l, k)
[k+1, r]段的分区方式数量：g[k+1][r]
应用模运算防止溢出
输出整个数组[1, n]的结果
时间复杂度：O(n³)，空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 501, mod = 1e9+7;

int g[N][N];
inline int get(const int l, const int r) {
    if (l == r) return 1;
    return g[l+1][r];
}

int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) g[i][i] = 1;//单元素数组有1种方法
    for (int len = 2; len <= n; ++len)
        for (int l = 1; l <= n - len + 1; ++l) {
            const int r = l + len - 1;
            g[l][r] = g[l+1][r];
            for (int k = l; k <= r-1; ++k)
                if (a[l] < a[k+1])
                    (g[l][r]+=1ll*get(l,k)*g[k+1][r]%mod)%=mod;
        }
    cout << get(1, n);
    return 0;
}