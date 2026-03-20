//
// Created by Psy.C on 2026/3/21.
//
/**
str[N]: 存储输入字符串
r[M]: 记录每个字母出现次数
c[M]: 存储出现奇数次的字母
n: 出现奇数次的字母种类数
将成对的奇数频次字母调整为偶数频次
保留一个字母多一次出现（为回文中心准备）
如果原始奇数频次字母数量为奇数，将中间的字母放在字符串中心
从两端向中心构造回文串
每次找一个出现次数≥2的字母，放在对称位置
减少该字母计数2次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 26;
char str[N];
int r[M], c[M], n;
int main() {
    fast;
    cin >> str; int len = strlen(str);
    for (int i = 0; i < len; ++i) r[str[i] - 'a']++;
    for (int i = 0; i < M; ++i)
        if (r[i]&1) c[n++] = i;
    for (int i = 0, j = n-1; i < j; ++i, --j)
        r[c[i]]++, r[c[j]]--;
    if (n&1) str[len/2] = c[n/2] + 'a';
    for (int i = 0, j = len-1, h = 0; i <= j; ++i, --j)
        for (; h < M; ++h)
            if (r[h] >= 2) {
                r[h] -= 2;
                str[i] = h + 'a'; str[j] = h + 'a';
                break;
            }
    cout << str;
    return 0;
}