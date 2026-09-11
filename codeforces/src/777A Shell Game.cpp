//
// Created by Psy.C on 2026/9/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[][3] = {
    0, 1, 2, 1, 0, 2, 1, 2, 0, 2, 1, 0, 2, 0, 1, 0, 2, 1
};
int main() {
    fast;
    int n, k; cin >> n >> k; n %= 6;
    cout << a[n][k] << '\n';
    return 0;
}