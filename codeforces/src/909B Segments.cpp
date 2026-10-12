//
// Created by Psy.C on 2026/10/11.
//
/**
特征方程：x^4 - 2x^3 + 0x^2 + 2x - 1 = 0（注意这里的符号整理）
a[n] = [ 1 + 4n + 2n² - (-1)^n ] / 8
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;
constexpr int N = 1e6;
int n, a[N]{0,1,2,4,6};
int main() {
    fast;
    cin >> n;
    rep(i,5,n) a[i] = 2*a[i-1] - 2*a[i-3] + a[i-4];
    cout << a[n];
    return 0;
}