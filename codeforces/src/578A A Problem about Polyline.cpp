//
// Created by Psy.C on 2026/3/15.
//
///给定正整数x, y，找到有理数r/s，使得在某种度量下|xr - ys|尽可能小，同时保持s尽可能大。
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x, y;
int main() {
    fast;
    cin >> x >> y;
    if (x < y) cout << "-1\n";
    else if (x == y) cout << y << '\n';
    else {
        double k1 = floor((x-y)/2/y), k2 = floor((x+y)/2/y);
        printf("%.9lf\n", min((x-y)/k1/2, (x+y)/k2/2));
    }
    return 0;
}