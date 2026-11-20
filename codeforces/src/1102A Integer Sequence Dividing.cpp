//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
n*(n+1)/2 是等差求和公式（1 加到 n）；
%2 取其奇偶性：0 表示偶数，1 表示奇数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin >> n;
    cout << (n*(n+1)/2)%2;
    return 0;
}