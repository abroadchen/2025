//
// Created by Psy.C on 2026/3/26.
//
/**
k1[M+5]：统计斜率为1的直线上点的数量
k2[M+5]：统计斜率为-1的直线上点的数量

k1[y-x+N]++：统计在直线y-x=c上的点数量
y-x+N：偏移N是为了处理负数索引，确保索引非负
这条直线的斜率为1
k2[y+x]++：统计在直线y+x=c上的点数量
这条直线的斜率为-1

ans：记录总的配对数
遍历所有可能的直线
(k1[i]*(k1[i]-1))>>1：计算k1[i]个点中任选2个的组合数C(k1[i],2)
C(n,2) = n*(n-1)/2
>>1：右移1位相当于除以2
同样计算k2数组中每条直线上的配对数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e3, M = N<<1;
int n, k1[M+5], k2[M+5];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        k1[y-x+N]++; k2[y+x]++;
    }
    ll ans = 0;
    for (int i = 0; i <= M; ++i) {
        if (k1[i]) ans += (k1[i]*(k1[i]-1))>>1;
        if (k2[i]) ans += (k2[i]*(k2[i]-1))>>1;
    }
    cout << ans << '\n';
    return 0;
}