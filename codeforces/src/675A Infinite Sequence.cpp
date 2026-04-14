//
// Created by Psy.C on 2026/4/13.
//
/**
a: 起始值
b: 目标值
c: 每次变化的步长

如果起始值a等于目标值b，可以直接到达（不需要任何操作）
输出"YES"并结束程序
如果步长c为0，意味着无法改变数值
只有当a=b时才能"到达"（实际上已经在目标位置）
否则永远无法到达目标
t1 = (b-a)%c: 计算(b-a)除以c的余数
t2 = (b-a)/c: 计算需要多少步才能从a到达b
if (t1 == 0 && t2 > 0):
t1 == 0: 表示(b-a)能被c整除，说明可以从a通过若干步c到达b
t2 > 0: 表示需要正数步，即b在a的前进方向上
如果两个条件都满足，输出"YES"
否则输出"NO"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    if (a == b) {
        cout << "YES\n";
        return 0;
    }
    if (c == 0) {
        if (a == b) cout << "YES\n";
        else cout << "NO\n";
    } else {
        int t1 = (b-a)%c, t2 = (b-a)/c;
        if (t1 == 0 && t2 > 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}