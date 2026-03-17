//
// Created by Psy.C on 2026/3/17.
//
/**
m：全局变量，用于字符偏移量
get(char c)：将字符c按照当前偏移量m进行变换
将字符转换为0-25的数字
加上偏移量m
对26取模（字母表循环）
转换回字符
m在1-104之间循环（当>104时重置为7）
n：字符串长度
t：目标相同的字符数
k：s1和s2中相同位置字符的个数
s1, s2：输入的两个字符串

(n-k)/2 + k：最多能得到的相同字符数
k：原本就相同的字符数
(n-k)/2：可以通过修改不同字符对获得的相同字符数
n-t：目标需要的相同字符数
如果最大可能的相同字符数小于目标，输出-1

处理相同字符位置：
如果当前字符对相同且还需要保留相同字符：输出原字符
否则：使用get()函数变换字符，确保与原字符不同
处理不同字符位置：
如果还需要增加相同字符（从s1取）：输出s1[i]
如果还需要增加相同字符（从s2取）：输出s2[i]
否则：使用get()函数找一个既不同于s1[i]也不同于s2[i]的字符

时间复杂度：
O(n)，只需遍历字符串一次
空间复杂度：
O(n)，用于存储输入字符串
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+5;

char m;
char get(char c) {
    m++;
    if (m > 104) m = 7;
    return (c - 'a' + m) % 26 + 'a';
}

int n, t, k;
char s1[N], s2[N];
int main() {
    scanf("%d %d", &n, &t); scanf("%s %s", s1+1, s2+1);
    for (int i = 1; i <= n; ++i)
        if (s1[i] == s2[i]) ++k;
    if ((n-k)/2 + k < n - t) { puts("-1"); return 0; }
    int x = 0, k1 = 0, k2 = 0; char c;
    for (int i = 1; i <= n; ++i) {
        if (s1[i] == s2[i]) {
            if (x < k && x < n - t) { printf("%c", s1[i]); ++x; }
            else {
                c = get(s1[i]);
                if (c == s1[i]) c = get(s1[i]);
                printf("%c", c);
            }
        } else {
            if (k + k1 < n - t) { printf("%c", s1[i]); ++k1; }
            else if (k + k2 < n - t) { printf("%c", s2[i]); ++k2; }
            else {
                c = get(s1[i]);
                while (c == s2[i] || c == s1[i]) c = get(s1[i]);
                printf("%c", c);
            }
        }
    }
    puts("");
    return 0;
}