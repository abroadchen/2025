//
// Created by Psy.C on 2026/3/31.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a;
int main() {
    fast;
    cin >> n >> a;
    if (a&1) cout << ((a+1)>>1) << '\n';
    else cout << ((n-a)>>1)+1 << '\n';
    return 0;
}