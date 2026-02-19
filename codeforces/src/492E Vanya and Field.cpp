//
// Created by Psy.C on 2026/2/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1000001;
int n, m, dx, dy, x, y, z, s[N], d[N];
int main() {
    fast;
    cin >> n >> m >> dx >> dy;
    for (int i = 0; i < n; ++i) {
        s[x] = y;//x坐标对应的y坐标
        x += dx; x %= n;//使坐标在[0,n-1]范围内循环
        y += dy; y %= n;
    }
    for (int i = 0, t, mx = 0; i < m; ++i) {
        cin >> x >> y;
        t = y - s[x];//实际y值与轨迹y值的差
        if (t < 0) t = n + t;
        d[t]++;//每个偏移量的出现次数
        if (d[t] > mx) mx = d[t], z = t;
    }
    cout << "0 " << z << '\n';
    return 0;
}