//
// Created by Psy.C on 2026/2/26.
//
/**
m：客人数量
t：蜡烛燃烧时间
r：每个客人需要的最小亮度
a[N]：客人到达时间数组
s[N]：每个时间点的亮度数组

如果单支蜡烛的燃烧时间t小于所需的亮度r
说明无论如何都无法满足要求，输出-1

从客人到达时间前1时刻开始向前查找
直到该客人的亮度达到要求r为止
从时间j+1开始，持续t个时间单位增加亮度
避免负时间索引
每点燃一支蜡烛，计数器加1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3001;
int m, t, r, a[N], s[N];
int main() {
    fast;
    cin >> m >> t >> r;
    for (int i = 0; i < m; ++i) cin >> a[i];
    if (t < r) {
        cout << "-1\n";
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < m; ++i)
        for (int j = a[i]-1; s[a[i]] < r; --j) {
            for (int k = j + 1; k <= j + t; ++k)
                if (k >= 0) s[k]++;
            ans++;
        }
    cout << ans << '\n';
    return 0;
}