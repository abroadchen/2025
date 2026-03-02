//
// Created by Psy.C on 2026/3/2.
//
/**
起点遍历：从字符串的每个位置i开始

步长遍历：j表示等差数列的公差
终止条件：i+j*4 < n 确保至少能形成5个元素的等差序列

等差序列检查：检查从位置i开始，步长为j的等差序列
序列位置：i+j*k 表示等差序列的第k个位置
中断条件：如果遇到'.'字符就停止检查
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
char str[101];
bool ok() {
    for (int i = 0; i < n; ++i)
        for (int j = 1, k; i+j*4 < n; ++j) {
            for (k = 0; i+j*k < n && k < 5; ++k)
                if (str[i+j*k] == '.')
                    break;
            if (k >= 5) return true;
        }
    return false;
}

int main() {
    fast;
    cin >> n >> str;
    if (ok()) cout << "yes\n"; else cout << "no\n";
    return 0;
}