//
// Created by Psy.C on 2026/3/27.
//
/**
a[]：原始数组
b[]：存储差值频次
c[]：存储乘积频次

c[s] 表示两个差值之和等于 s 的方案数
对于差值i和差值j，它们的组合数为 b[i] * b[j]
存储在 c[i+j] 中
计算c数组的前缀和
c[i] 现在表示两个差值之和 ≤ i 的总方案数

对于每个差值 a[i] - a[j]
查找有多少个"两个差值之和"小于这个差值
即查找 c[a[i] - a[j] - 1]

总的可能组合数是 C(n,2)³ = (n*(n-1)/2)³
res 是满足条件的组合数
时间复杂度：O(M² + n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
const int N = 1e5+5, M = 5e3, K = 1e4;
ll n, a[N], b[N], c[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            b[a[i] - a[j]]++;
    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= M; ++j)
            c[i+j] += b[i] * b[j];
    for (int i = 1; i <= K; ++i) c[i] += c[i-1];
    ll res = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            res += c[a[i] - a[j] - 1];
    double ans = 1.*res/pow(n*(n-1)/2, 3);
    printf("%.12lf\n", ans);
    return 0;
}