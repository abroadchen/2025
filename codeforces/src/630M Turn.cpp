//
// Created by Psy.C on 2026/3/29.
//
/**
将角度转换到 [-180, 180] 范围内：

如果 x > 180，转换为负值：x = x - 360
如果 x < -180，转换为正值：x = x + 360

将360°分为4个扇形区域：

flag = 0: [-45°, 45°] → 东/右方向
flag = 1: (45°, 135°] → 北/上方向
flag = 2: (135°, 180°] ∪ [-180°, -135°] → 西/左方向
flag = 3: (-135°, -45°) → 南/下方向

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll x;
int main() {
    fast;
    cin >> x; x = x%360;
    if (x > 180) x -= 360;
    else if (x < -180) x += 360;
    int flag;
    if (x <= 45 && x >= -45) flag = 0;
    else if (x <= 135 && x > 45) flag = 1;
    else if (x > 135 || x <= -135) flag = 2;
    else flag = 3;
    cout << flag << '\n';
    return 0;
}