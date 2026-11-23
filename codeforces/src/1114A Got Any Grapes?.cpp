//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
a,b,c = 当前各自拥有量，x,y,z = 各自目标
实话说，这段写法比较"绕"：x -= a 用 x 存剩余额，y += x 把该剩余额追加到第二级。其实等价于 y += (a - x)（若 a>x）
若第二级当前存量 b 超过其当前目标 y → NO。
否则把第二级富余传给第三级：y -= b 后 y 是剩余额，z += y 追加给第三级
第三级只要不超过目标 z 即可输出 YES（因为它是最后一级，富余可以堆着不浪费）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int a, b, c, x, y, z;
int main() {
    fast;
    cin >> a >> b >> c >> x >> y >> z;
    if (a > x) { cout << "NO"; return 0; }
    x -= a; y += x;
    if (b > y) { cout << "NO"; return 0; }
    y -= b; z += y;
    if (c > z) { cout << "NO"; return 0; }
    cout << "YES";
    return 0;
}