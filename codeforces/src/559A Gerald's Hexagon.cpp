//
// Created by Psy.C on 2026/3/11.
//
/**
大正方形面积：(a + b + f)²
减去三个小正方形面积：b², d², f²
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c, d, e, f;
int main() {
    fast;
    cin >> a >> b >> c >> d >> e >> f;
    cout << (a + b + f) * (a + b + f) - b * b - d * d - f * f;
    return 0;
}