//
// Created by Psy.C on 2026/1/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, st = 0; cin >> n;
    bool flag = true;
    while (n != 0) {
        const int d = n % 10; n /= 10;//从右到左逐位处理数字
        if (d == 1)  st = 0;
        else if (d == 4 && st < 2) st += 1;
        else flag = false;//无效数字或连续'4'太多
    }
    if (st != 0) flag = false;//有未正确重置的尾随'4'
    cout << (flag ? "YES\n" : "NO\n");
    return 0;
}