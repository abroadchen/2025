//
// Created by Psy.C on 2025/11/24.
//
/*
 *保证a是较长(或等长)的字符串，b是较短的字符串
 *
*字符串b的后缀与字符串a的前缀对齐：
i从1开始，表示b的起始比较位置
k从i开始遍历b，j从0开始遍历a
统计匹配字符数num
更新最小操作数：len - num（len是较短字符串的长度）
 *
*字符串a从位置i开始的子串与字符串b对齐：
i从0开始，表示a的起始比较位置
k从i开始遍历a，j从0开始遍历b
统计匹配字符数num
更新最小操作数：len - num
 *
*时间复杂度：O(len1 × len2)
空间复杂度：O(1)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) ((int)(x).size())
using namespace std;

string a, b;

int main() {
    fast;
    cin >> a >> b;
    int len1 = sz(a), len2 = sz(b), ans = 1e7;
    const int len = len2;
    if (len1 < len2) { swap(a, b);  swap(len1, len2); }
    for (int i = 1; i < len2; ++i) {
        int num = 0;
        for (int k = i, j = 0; k < len2 && j < len1; ++k, ++j) {
            if (b[k] == a[j]) num++;
        }
        ans = min(ans, len - num);
    }
    for (int i = 0; i < len1; ++i) {
        int num = 0;
        for (int k = i, j = 0; j < len2 && k < len1; ++j, ++k) {
            if (a[k] == b[j]) num++;
        }
        ans = min(ans, len - num);
    }
    cout << ans << '\n';
    return 0;
}