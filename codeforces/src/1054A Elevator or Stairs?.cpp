//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
x：电梯当前所在的楼层
y：你动身时所在的楼层（你的起点）
z：你的目标楼层
t1：走楼梯时每层花费的时间
t2：坐电梯每跨越一层花费的时间
t3：电梯开关门所耗费的固定时间
左边：走"电梯路线"的总时间

abs(y-x)   // 你所在楼层 y 到电梯所在楼层 x 的距离（先走到电梯）
abs(z-x)   // 电梯从 x 开到目标 z 的距离
(abs(z-x)+abs(y-x))*t2   // 电梯移动（跨层）总耗时
3*t3                      // 3 次开/关门
右边：走"全程爬楼梯"路线

abs(x-y)      // 从 y 到 x 的距离——注意这里其实是选用某段距离
abs(x-y)*t1   // 爬楼梯耗时（按 t1 每层）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int x, y, z, t1, t2, t3;
int main() {
    fast;
    cin >> x >> y >> z >> t1 >> t2 >> t3;
    if ((abs(z-x)+abs(y-x))*t2+3*t3 <= abs(x-y)*t1) cout << "YES";
    else cout << "NO";
    return 0;
}