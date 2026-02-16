//
// Created by Psy.C on 2026/2/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c, d, e, ans;
int main() {
    fast;
    cin >> a >> b >> c >> d >> e;
    const int sum = a + b + c + d + e;
    if (sum % 5 == 0) ans = sum / 5;
    cout << (sum%5 || ans == 0 ? -1 : sum/5) << '\n';
    return 0;
}