//
// Created by Psy.C on 2026/10/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10;

int n, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) { cin >> x; b[x]++; }
    for (int i : b)
        if (i%2 == 1) { cout << "Conan"; return 0; }
    cout << "Agasa";
    return 0;
}