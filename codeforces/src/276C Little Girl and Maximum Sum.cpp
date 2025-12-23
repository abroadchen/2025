//
// Created by Psy.C on 2025/12/23.
//O(n log n + q)
/*
*差分数组是一种技巧，用于将区间操作从O(n)优化到O(1)
通过记录相邻元素的差值来表示原数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200000
using namespace std;


int main() {
    fast;
    int n, q, a[N], l, r, c[N] = {}; cin>>n>>q;
    for (int i = 0; i < n; ++i) cin>>a[i];
    while (q--) {
        cin>>l>>r;
        c[l-1]++; c[r]--;//O(n*q)的暴力区间更新优化为O(q+n)
    }
    for (int i = 1; i < n; ++i) c[i] += c[i-1];//每个位置被覆盖的次数
    sort(a, a + n); sort(c, c + n);
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans += 1ll * a[i] * 1ll * c[i];//计算最大加权和：将最小的a值与最小的c值配对
    cout<<ans<<'\n';
    return 0;
}