//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
第一行 2000：数组长度。
接下来 M-2 = 1998 个 0 。
最后两个数：-(x - (x+k)/M) 和 x
x + k 必能被 2000 整除，(x+k)/2000 是精确整数，无误差
p = -(x - (x+k)/2000) = (x+k)/2000 - x。
总和 = p + x = (x+k)/2000
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e6, M = 2e3;
int k;
int main() {
    fast;
    cin >> k;
    int num = k%M, x = N-num;
    cout << "2000\n";
    rep(i,M-2) cout << "0 ";
    cout << -(x-(x+k)/M) << ' ' << x << '\n';
    return 0;
}