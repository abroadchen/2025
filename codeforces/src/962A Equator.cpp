//
// Created by Psy.C on 2026/10/21.
//
/**
读入 a[i] 后立刻 a[i] += a[i-1]，即在原地把 a 变成前缀和数组：
a[i] = 原a[1] + 原a[2] + ... + 原a[i]。
可确证：读完输入后，a[i] 即为前 i 个元素之和（前缀和），a[n] 为总和
(a[n]+1)/2 是总和向上取整的一半（向上取整，因为 (a[n]+1)/2 对整数除法是"不小于 a[n]/2 的最小整数"）。
从头遍历前缀和，找到第一个满足 a[i] >= 半值总和 的下标 i，输出它并结束。
可确证：从头找出第一个前缀和 a[i] 达到 ceil(a[n]/2) 的下标并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(int i=1;i<=(n);i++)
using namespace std;

constexpr int N = 2e5+5;

ll a[N];
int main() {
    fast;
    int n; cin >> n;
    rep(i,n) { cin >> a[i]; a[i] += a[i-1]; }
    rep(i,n) if (a[i] >= (a[n]+1)/2) { cout << i << '\n'; return 0; }
    return 0;
}