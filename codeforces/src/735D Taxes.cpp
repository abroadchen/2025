//
// Created by Psy.C on 2026/4/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

///判断数字x是否为素数
bool check(int x) {
    if (x <= 1) return false;
    for (int i = 2; i*i <= x; ++i)
        if (x%i == 0) return false;//找到因子
    return true;
}

int n;
int main() {
    fast;
    cin >> n;
    if (check(n)) cout << 1 << '\n';//n是素数
    else {
        if (n%2 == 0) cout << 2 << '\n';//每个大于2的偶数都可以表示为两个素数之和
        else {
            if (check(n-2)) cout << 2 << '\n';//n可以表示为2 + (n-2)，即两个素数之和，输出2
            else cout << 3 << '\n';//每个大于5的奇数都可以表示为三个素数之和
        }
    }
    return 0;
}