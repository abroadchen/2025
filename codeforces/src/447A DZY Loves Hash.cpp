//
// Created by Psy.C on 2026/2/9.
//
///时间复杂度：O(min(n,p)) 空间复杂度：O(p)
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int p, n, num[305];

int main() {
    fast;
    cin >> p >> n;
    int ans = -1;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (num[x%p]) { ans = i; break; }//该余数是否已标记过
        num[x%p] = 1;
    }
    cout << ans;
    return 0;
}