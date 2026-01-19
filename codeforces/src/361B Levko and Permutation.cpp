//
// Created by Psy.C on 2026/1/19.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    if (n == k) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (i == 1) cout << (k+1)%n+1;//确保输出的是 [1, n] 范围内的有效排列
        else if (i-1<=k) cout << ' ' << i;
        else cout << ' ' << i%n+1;
    }
    cout << '\n';
    return 0;
}