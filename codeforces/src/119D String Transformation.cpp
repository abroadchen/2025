//
// Created by Psy.C on 2025/11/16.
//
/*
*n: 字符串长度
z[N]: Z数组，用于Z算法  计算每个位置开始的最长公共前缀
z2[N]: 第二个Z数组 用于字符串a与b的匹配
p[N]: KMP算法的失败函数数组
p2[N]: 第二个KMP数组
a, b: 输入的两个字符串
ra: 字符串a的反转
 *
*Z算法函数：
z[0] = n: 第一个位置的Z值设为字符串长度
a += 1, b += 2: 给字符串添加哨兵字符
Z算法核心：计算字符串b与其自身各个后缀的最长公共前缀
l, r: 维护当前最右的匹配区间
*计算字符串a与字符串b的Z数组z2
用于查找a的每个后缀与b的最长公共前缀
 *
*计算字符串b的失败函数数组p
p[i]表示b[0..i]的最长相等前后缀长度
*在字符串a中查找字符串b
结果存储在p2数组中
 *
 *a[i] == b[n-i-1]（前缀和后缀对应位置相等）
 *记录最后一个满足条件的位置对
 *
*时间复杂度：
O(n) - 线性时间复杂度
空间复杂度：
O(n) - 线性空间复杂度
 */
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e6+9;
int n, z[N], z2[N], p[N], p2[N];
string a, b, ra;

void f(string& a, string& b) {
    int i, l, r;
    for (z[0] = n, i = 1, a += 1, b += 2, l = r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);//当前位置到Z-box右边界的距离
        while (b[i + z[i]] == b[z[i]]) ++z[i];//增加匹配长度z[i]
        if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
    for (i = 0, l = r = -1; i < n; ++i) {//字符串a的后缀与字符串b的前缀的匹配长度
        if (i <= r) z2[i] = min(z[i - l], r - i + 1);
        while (a[i + z2[i]] == b[z2[i]]) ++z2[i];
        if (i + z2[i] - 1 > r) r = i + z2[i] - 1, l = i;
    }
}

void kmp(string& a, string& b) {
    int i, j;//j: 当前匹配长度
    for (i = 1, j = 0; i < n; ++i) {
        while (j && b[i] != b[j]) j = p[j - 1];//利用已计算的失效函数回退
        if (b[i] == b[j]) p[i] = ++j;//增加匹配长度并记录到p[i]
    }
    for (i = j = 0; i < n; ++i) {//在字符串a中查找字符串b
        while (j && a[i] != b[j]) j = p[j - 1];
        if (a[i] == b[j]) p2[i] = ++j;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int ai(-1), aj(-1), i, j;
    if (getline(cin, a), getline(cin, b),
        n = a.size(), n != b.size()) return cout << "-1 -1", 0;
    ra = a;
    reverse(ra.begin(), ra.end());
    f(a, b), kmp(b, ra);
    for (i = 0; i < n - 1 && a[i] == b[n - i - 1]; ++i) {//a的前缀与b的后缀对应位置字符相同的点
        j = n - p2[n - i - 2];//根据KMP匹配结果计算位置j
        if (z2[i + 1] >= j - i - 1) ai = i, aj = j;
    }
    cout << ai << ' ' << aj;
    return 0;
}