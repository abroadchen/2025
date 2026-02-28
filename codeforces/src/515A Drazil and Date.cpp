//
// Created by Psy.C on 2026/2/28.
//
/**
a, b：目标坐标的x和y值
s：允许的最大步数

从原点(0,0)到目标点(a,b)的曼哈顿距离
到达目标点所需的最少步数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, s;
int main() {
    fast;
    cin >> a >> b >> s;
    if (const int mn = abs(a) + abs(b); mn > s) cout << "No\n";
    else {
        if (mn&1 && s&1) cout << "Yes\n";
        else if (mn%2 == 0 && s%2 == 0) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}