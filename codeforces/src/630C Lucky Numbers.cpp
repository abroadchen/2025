//
// Created by Psy.C on 2026/3/29.
//
///2^1 + 2^2 + 2^3 + ... + 2^n = 2^(n+1) - 2
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll dfs(int x) {
    if (x == 1) return 2;
    return dfs(x - 1) + (1ll<<x);
}

int n;
int main() {
    fast;
    cin >> n;
    cout << dfs(n) << '\n';
    return 0;
}