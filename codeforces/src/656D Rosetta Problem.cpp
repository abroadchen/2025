//
// Created by Psy.C on 2026/4/8.
//
///O(log₈n)，因为每次循环都将n除以8，总共需要log₈n次操作
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, s;
int main() {
    fast;
    cin >> n;
    while (n > 0) {
        //等价于 n % 8 == 1
        if ((n-1)%8 == 0) s++;//检查条件并计数
        n /= 8;//去掉最后一位八进制数字
    }
    cout << s;
    return 0;
}