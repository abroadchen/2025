//
// Created by Psy.C on 2026/1/12.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1001
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    int a[N], cnt = 0;
    for (const char i : s) {
        if (i == '+') continue;
        a[cnt++] = i - '0';//数字字符，转换为整数值（i - '0'）并存入数组
    }
    sort(a, a + cnt);
    for (int i = 0; i < cnt; ++i) {
        cout << a[i];
        if (i == cnt - 1) break;
        cout << '+';//每个数字后（除了最后一个）添加+号
    }
    return 0;
}