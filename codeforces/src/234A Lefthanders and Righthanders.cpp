//
// Created by Psy.C on 2025/12/12.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n; cin>>n;
    vector<char> a(n+1);
    for (int i = 1; i <= n; ++i) cin>>a[i];
    for (int i = 1; i <= n / 2; ++i) {
        const int j = i + n / 2;
        if (a[i] == 'L' && a[j] == 'R')
            cout << i << ' ' << j << '\n';
        else cout << j << ' ' << i << '\n';
    }
    return 0;
}