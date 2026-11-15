//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
操作类型 参数1 参数2。
构造另一条指令 2 i (x+4000-i)。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    cout << n << '\n';
    cout << "1 " << n << " 4000\n";
    for (int i = 1, x; i < n; i++) {
        cin >> x;
        cout << "2 " << i << ' ' << x+4000-i << '\n';
    }
    return 0;
}