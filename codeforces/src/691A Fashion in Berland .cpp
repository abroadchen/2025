//
// Created by Psy.C on 2026/4/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n;
bool a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (n == 1) {
        if (a[1]) cout << "YES\n"; else cout << "NO\n";
        return 0;
    }
    int j = 0;
    for (int i = 1; i <= n; ++i)
        if (!a[i]) j++;//!a[i]表示a[i]为false时条件成立
    if (j != 1) cout << "NO\n"; else cout << "YES\n";
    return 0;
}