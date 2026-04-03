//
// Created by Psy.C on 2026/4/2.
//
/**
如果a+b=2，返回0
否则返回：a+b-2-是否(a-b能被3整除)
如果(a-b)%3 == 0，结果为1
如果(a-b)%3 ≠ 0，结果为0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b;
int main() {
    fast;
    cin >> a >> b;
    cout << (a + b == 2 ? 0 : a + b - 2 - !((a - b)%3)) << '\n';
    return 0;
}