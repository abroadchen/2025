//
// Created by Psy.C on 2026/4/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k;
int main() {
    fast;
    cin >> n >> k;
    cout << k*(n/k+1) << '\n';
    return 0;
}