//
// Created by Psy.C on 2026/9/24.
//
/**
a：原表（pattern），通常是 "abcdefghijklmnopqrstuvwxyz"（小写字母表）。
b：替换表，与 a 一一对应（a[j] 替换成 b[j]）。
c：待处理的文本。
用 scanf 读三个不含空格的字符串
（1）判断是否为大写字母，并记录 flag
若 c[i] 是大写字母：记 flag=1，并把 c[i] 转成小写（'A'→'a'），这样后面查表时统一用 a（小写字母表）匹配
（2）数字直接输出
数字 0-9 不属于字母，直接原样打印，不做替换。
（3）字母查表替换
在映射表 a 中查找 c[i]（已统一为小写）的位置 j。
找到后输出替换字符 b[j]：
若原字符是大写（flag=1）：b[j]+'A'-'a' 把 b[j]（假定小写）转回大写。
若原字符是小写：直接输出 b[j]
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1005;
char a[N], b[N], c[N];
int main() {
    scanf("%s%s%s", a, b, c);
    int len = strlen(c);
    for (int i = 0; i < len; ++i) {
        int flag = 0;
        if (c[i] >= 'A' && c[i] <= 'Z') { flag = 1; c[i] = c[i] - 'A' + 'a'; }
        if (c[i] >= '0' && c[i] <= '9') printf("%c", c[i]);
        else {
            for (int j = 0; j < 26; ++j) {
                if (c[i] == a[j]) {
                    if (flag) printf("%c", b[j]+'A'-'a');
                    else printf("%c", b[j]);
                }
            }
        }
    }
    puts("");
    return 0;
}