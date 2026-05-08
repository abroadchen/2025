//
// Created by Psy.C on 2026/5/8.
//
///O(log k)，因为每次循环都会将k除以2
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, ans = 1;
int main() {
    fast;
    cin >> n >> k;
    while (k%2 == 0) {
        k /= 2;
        ans++;//k中包含的因子2的个数
    }
    cout << ans << '\n';
    return 0;
}