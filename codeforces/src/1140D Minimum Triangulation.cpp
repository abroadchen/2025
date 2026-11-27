//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
ans = 2×3 + 3×4 + 4×5 + ... + (n-1)×n

等价于 Σ (i² + i)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll ans;
int main() {
    fast;
    cin >> n;
    for (int i = 2; i < n; i++) ans += i*(i+1);
    cout << ans;
    return 0;
}