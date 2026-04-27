//
// Created by Psy.C on 2026/4/26.
//
/**
mx - 记录最大间隔距离（初始化为0，默认值）
z = -1 - 记录上一个元音字母的位置（初始设为-1）
x - z - 计算当前位置与上一个元音字母位置的距离
mx = max(mx, x - z) - 更新最大距离记录
z = x - 将当前位置更新为新的元音字母位置
mx - 字符串内部相邻元音字母间的最大距离
(int)p.size()-z - 最后一个元音字母到字符串末尾的距离
时间复杂度：O(n)，单次遍历字符串
空间复杂度：O(1)，仅使用常数额外空间
边界处理：通过初始值z=-1巧妙处理第一个字符前的情况
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string p;
int mx, z = -1;
int main() {
    fast;
    cin >> p;
    for (int x = 0; x < p.size(); ++x)
        if (p[x] == 'A' || p[x] == 'E' || p[x] == 'I' ||
            p[x] == 'O' || p[x] == 'U' || p[x] == 'Y')
            mx = max(mx, x - z), z = x;
    cout << max(mx, (int)p.size()-z);
    return 0;
}