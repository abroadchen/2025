//
// Created by Psy.C on 2025/12/26.
//
/*
 * f[t] - f[s] = 第s+1条边到第t条边的总长度
*f[n+1]：整个环的总周长
f[n+1] - dis：从s到t的反向距离（绕环的另一半）
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, f[102] = {}; cin >> n;
    for (int i = 2, d; i < n + 2; ++i) {
        cin >> d;
        f[i] = f[i-1] + d;
    }
    int s, t; cin >> s >> t;
    if (s > t) swap(s, t);
    const int dis = f[t] - f[s];
    cout << min(dis, f[n+1] - dis) << '\n';
    return 0;
}