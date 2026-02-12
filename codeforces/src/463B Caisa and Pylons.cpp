//
// Created by Psy.C on 2026/2/12.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;

int main() {
    fast;
    cin >> n;
    int ans = 0;
    for (int i = 0, h; i < n; ++i) {
        cin >> h;
        ans = max(ans, h);
    }
    cout << ans << '\n';
    return 0;
}