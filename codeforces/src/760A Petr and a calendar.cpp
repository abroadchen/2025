//
// Created by Psy.C on 2026/9/4.
//
/**
当 m=2 且 n=1 时，直接输出 4
第一类：m 属于 {1,3,5,7,8,10,12}，且 n <= 5。
第二类：m 属于 {4,6,9,11}，且 n <= 6。
第三类：m == 2，且 n <= 7
如果以上所有条件都不满足，则输出 6
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int m, n; cin >> m >> n;
    if (m == 2 && n == 1) { cout << "4\n"; return 0; }
    if ((m==1||m==3||m==5||m==7||m==8||m==10||m==12) && n <= 5) {
        cout << "5\n"; return 0;
    }
    if ((m==4||m==6||m==9||m==11) && n <= 6) {
        cout << "5\n"; return 0;
    }
    if (m == 2 && n <= 7) { cout << "5\n"; return 0; }
    cout << "6\n";
    return 0;
}