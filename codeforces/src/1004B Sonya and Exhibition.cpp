//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
读入一个整数 n，表示要输出的字符个数
循环 i 从 0 到 n-1，每次输出 i & 1（i 的二进制最低位）：

i 为偶数（0,2,4,…）时，i&1 = 0
i 为奇数（1,3,5,…）时，i&1 = 1
所以输出结果是：01010101...（n 位，以 0 开头交替）
输出换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cout << (i&1);
    cout << '\n';
    return 0;
}