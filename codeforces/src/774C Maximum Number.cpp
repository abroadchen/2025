//
// Created by Psy.C on 2026/9/11.
//
/**
n 根火柴棒摆出一个尽量大的数，其中数字 8 用 7 根（或配合其他计数），1 用 2 根。算法是：

若 n 为奇数（n mod 2=1）：
先输出一个 7（因为 7 需要 3 根火柴棒，且以 7 开头能比 1 更大）；
n := n-3，把用掉的 3 根减掉，此时 n 变为偶数。
之后 n 一定是偶数，每 2 根输出一个 1（for i:=1 to n div 2 do write(1)），用最少的火柴（每根用 2 根）凑足位数，使位数最多、数值最大。
writeln 换行。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

map<int, int> mp;
int main() {
    fast;
    mp[3] = 7; mp[2] = 1;
    int n; cin >> n;
    int mx = n/2, res = n%2;
    for (int i = 0; i < mx; ++i) {
        cout << mp[res+2];
        res = 0;
    }
    cout << '\n';
    return 0;
}