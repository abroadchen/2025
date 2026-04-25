//
// Created by Psy.C on 2026/4/24.
//
/**
情况1: (n + n%2) % 4 == 0
如果n是偶数: (n + 0) % 4 == 0，即n是4的倍数
如果n是奇数: (n + 1) % 4 == 0，即n+1是4的倍数
此时 x = n/2
情况2: 其他情况
x = n - n%2：将n变为偶数（如果是奇数就减1）
x = x/2 + 1：除以2再加1
等价于 x = n/2 + 1（当n为偶数时）

(x-1)*8: 基础值，每层8个单位
(x-1)%2: 调整项，当x-1为奇数时减1
get(s): 字符偏移量

时间复杂度: O(1) - 常数时间计算
空间复杂度: O(1) - 常数空间使用
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

///将特定字符映射到数字
int get(char s) {
    if (s == 'f') return 1;
    if (s == 'e') return 2;
    if (s == 'd') return 3;
    if (s == 'a') return 4;
    if (s == 'b') return 5;
    if (s == 'c') return 6;
    return 0;
}

ll n;
char s;
int main() {
    fast;
    cin >> n >> s; ll x;
    if ((n + n%2)%4 == 0) x = n/2;
    else {
        x = n - n%2;
        x = x/2 + 1;
    }
    cout << (x-1)*8 - (x-1)%2 + get(s) << '\n';
    return 0;
}