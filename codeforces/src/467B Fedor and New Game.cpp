//
// Created by Psy.C on 2026/2/13.
//
///二进制表示中1的个数，也就是汉明距离
///两个等长字符串在相应位置上不同字符的个数
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;

int n, m, k, a[N];

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) cin >> a[i];
    cin >> a[m];
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        int cnt = 0;
        for (int x = a[i]^a[m]; x; x >>= 1) if (x&1) cnt++;
        if (cnt <= k) ans++;
    }
    cout << ans << '\n';
    return 0;
}