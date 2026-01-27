//
// Created by Psy.C on 2026/1/28.
//
/**
* j - i: 连续'0'的长度（从位置 i 到 j-1）
i: 当前'0'段之前的部分长度
条件分析：

j - i > i: 如果连续'0'的长度大于其之前的字符串长度
j - i == i && a[i] > a[0]: 如果'0'长度等于之前长度且当前字符大于首字符
满足任一条件时，将 ans 设为1
否则，ans++

时间复杂度
O(n)，虽然有嵌套循环，但 i 和 j 都只向前移动
空间复杂度
O(n)，用于存储输入字符串
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1500000
using namespace std;


int main() {
    fast;
    char a[N]; cin >> a;
    int ans = 0, j;//内层循环的索引
    const int n = static_cast<int>(strlen(a));
    for (int i = 0; i < n; i = j) {//每次跳跃到 j
        for (j = i + 1; j < n; ++j) if (a[j] != '0') break;//寻找第一个非'0'字符
        if (j - i > i || j - i == i && a[i] > a[0]) ans = 1;
        else ans++;
    }
    cout << ans << '\n';
    return 0;
}