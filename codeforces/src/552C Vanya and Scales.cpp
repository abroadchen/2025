//
// Created by Psy.C on 2026/3/10.
//
/**
w：进制数
m：待检查的数字

当m不为0时继续循环
检查m在w进制下的系数是否在{-1, 0, 1}范围内：
如果 (m-1)%w == 0：m ≡ 1 (mod w)，系数为1，减1使m变为w的倍数
如果 m%w == 0：m ≡ 0 (mod w)，系数为0，无需操作
如果 (m+1)%w == 0：m ≡ -1 (mod w)，系数为-1，加1使m变为w的倍数
否则：系数不在{-1, 0, 1}范围内，输出"NO"
O(log_w m)，每次循环将m除以w
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int w, m;
int main() {
    fast;
    cin >> w >> m;
    while (m) {
        if ((m-1)%w == 0) m--;
        else if (m%w == 0) {}
        else if ((m+1)%w == 0) m++;
        else {
            cout << "NO";
            return 0;
        }
        m /= w;
    }
    cout << "YES";
    return 0;
}