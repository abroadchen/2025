//
// Created by Psy.C on 2026/1/16.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, s1 = 0, s2 = 0, flag = 0; cin >> n;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        s1 += a; s2 += b;
        if ((a + b) % 2) flag = 1;
    }
    if (s1 % 2 == 0 && s2 % 2 == 0) { cout << "0\n"; return 0; }//不需要任何操作就能满足条件
    if ((s1 + s2) % 2) { cout << "-1\n"; return 0; }//不可能分成两个相等的部分
    if (flag) { cout << "1\n"; return 0; }//只需要一次操作就能解决问题
    cout << "-1\n";
    return 0;
}