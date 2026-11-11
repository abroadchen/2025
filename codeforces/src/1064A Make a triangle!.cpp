//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
若 x 是最大边且不满足条件：x >= y+z。
此时 x 至少要缩减到 y+z-1（减到 y+z 仍不构成，需再小 1）。
需减掉的长度 = x - (y+z-1) = x-(y+z)+1。
更新 ans
同上，若 y 是最大边不成立：需减 y-(x+z)+1
同上，若 z 是最大边不成立：需减 z-(x+y)+1
若上面三个都不满足，说明任意两边之和都大于第三边，即能构成三角形，ans = 0
输出最少需要剪掉的长度 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int inf = 1e8;

int x, y, z, ans;
int main() {
    fast;
    cin >> x >> y >> z; ans = inf;
    if (x >= y+z) ans = min(x-(y+z)+1, ans);
    else if (y >= x+z) ans = min(ans, y-(x+z)+1);
    else if (z >= x+y) ans = min(ans, z-(x+y)+1);
    else ans = 0;
    cout << ans;
    return 0;
}