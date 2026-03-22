//
// Created by Psy.C on 2026/3/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a1, a2, a3, t1, t2, t3;
int main() {
    fast;
    cin >> a1 >> a2 >> a3;
    cin >> t1 >> t2 >> t3;
    int c1 = a1 - t1, c2 = a2 - t2, c3 = a3 - t3;
    if (c1 >= 0 && c2 >= 0 && c3 >= 0) cout << "Yes\n";
    else {
        if (c1 > 0) c1 >>= 1;
        if (c2 > 0) c2 >>= 1;
        if (c3 > 0) c3 >>= 1;
        if (c1 + c2 + c3 >= 0) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}