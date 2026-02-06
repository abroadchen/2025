//
// Created by Psy.C on 2026/2/6.
//
/**
t2 %= 2：取t2对2的余数（奇偶性判断）
如果t2为奇数（存在奇数个200）：
需要至少2个100来配对形成一个可行方案
如果100的个数少于2，则无解，输出"NO"
否则从100的个数中减去2个
如果剩余的100个数为奇数，无法完全配对，输出"NO"
否则输出"YES"
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int t = 0, t1 = 0, t2 = 0, a[101];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; t += a[i];
        if (a[i] == 100) t1++; else t2++;
    }
    t2 %= 2;
    if (t2) {
        if (t1 < 2) { cout << "NO"; return 0; }
        t1 -= 2;
    }
    if (t1 % 2 != 0) { cout << "NO"; return 0; }
    cout << "YES";
    return 0;
}