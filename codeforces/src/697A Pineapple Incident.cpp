//
// Created by Psy.C on 2026/4/17.
//
/**
t: 初始值
s: 步长或间隔
x: 目标值
a1 = (x-t) / s：直接到达x所需步数
a2 = (x-t-1) / s：先+1再到达x所需步数

a1 是非负整数：(a1 == (int)a1 && a1 >= 0)
表示可以通过恰好 a1 次步长为s的操作从t到达x
a2 是正整数：(a2 == (int)a2 && a2 > 0)
表示可以通过先+1，然后 a2 次步长为s的操作从t到达x

时间复杂度：O(1)
空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int t, s, x;
int main() {
    fast;
    cin >> t >> s >> x;
    double a1 = (x-t)*1./(s*1.), a2 = (x-t-1)*1./(s*1.);
    if (a1 == (int)a1 && a1 >= 0 ||
        a2 == (int)a2 && a2 > 0) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}