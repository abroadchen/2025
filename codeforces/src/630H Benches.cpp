//
// Created by Psy.C on 2026/3/29.
//
/**
分子：n * (n-1) * ... * (n-m+1)
分母：m! = 1 * 2 * ... * m
A(n,m) = n! / (n-m)! = n * (n-1) * ... * (n-m+1)
C(n,5) * A(n,5) = A(n,5)² / 5!
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll C(int n, int m) {
    ll res = 1;
    for (int i = 0; i < m; ++i)
        res *= n - i;
    ll res2 = 1;
    for (int i = 0; i < m; ++i)
        res2 *= i + 1;
    return res/res2;
}
ll A(int n, int m) {
    ll res = 1;
    for (int i = 0; i < m; ++i)
        res *= n - i;
    return res;
}

int n;
int main() {
    fast;
    cin >> n;
    cout << C(n, 5)*A(n, 5) << '\n';
    return 0;
}