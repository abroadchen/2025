//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int m, n, l, r; cin>>m>>n;
    cout << min(m + 1, n + 1) << '\n';
    l = 0, r = max(m, n);
    while (l <= min(m, n)) {
        if (m <= n) cout << l++ << ' ' << r-- << '\n';//输出l r，然后l自增，r自减
        else cout << r-- << ' ' << l++ << '\n';
    }
    return 0;
}