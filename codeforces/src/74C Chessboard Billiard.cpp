//
// Created by Psy.C on 2025/11/4.
//
/*
*在一个n×m的网格中，从(0,0)到(n-1,m-1)的直线会穿过 gcd(n-1,m-1) + 1 个格子
或者等价地说，从(1,1)到(n,m)的直线会穿过 gcd(n-1,m-1) + 1 个格子
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    cout << __gcd(n - 1, m - 1) + 1;
    return 0;
}