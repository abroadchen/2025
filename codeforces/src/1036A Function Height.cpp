//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
当 b 能被 a 整除时，(b+a-1)/a = b/a（余数不影响），结果是精确商；
当 b 不能被 a 整除时，b + a - 1 相当于给被除数补上不足的部分，使结果自动进位到下一个整数。
等价于数学上的 ⌈b/a⌉（天花板除法）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b;
int main() {
    fast;
    cin >> a >> b;
    cout << (b+a-1)/a;
    return 0;
}