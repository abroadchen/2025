//
// Created by Psy.C on 2025/11/6.
//
/*
*cnt: 计数器，用于记录特殊字符的状态循环
cur: 当前字符的类型标识
pre: 前一个字符的类型标识
 *
 *cnt == 1表示这是连续出现的同类字符中的第一个
 *
 *pre (前一个字符存在且非零)
 *
*i (不是第一个字符)
i是当前字符在字符串中的索引位置
由于索引从0开始，i为0时表示处理第一个字符
这个条件确保不是在处理字符串的第一个字符（索引为0），因为第一个字符前面没有字符
 */
#include <cstdio>
using namespace std;

const int N = 1000;
char s[N];
int cnt(0), cur(0), pre(0);

int main() {
    gets(s);
    for (int i = 0; s[i]; ++i) {
        if (s[i] == ' ') continue;
        if (s[i] >= '0' && s[i] <= '9') cur = 1;
        else if (s[i] == ',') cur = 2;
        else { cur = 3; cnt = (cnt % 3) + 1; }

        if ((pre && cur == 3 && cnt == 1) ||
            (i && pre == 1 && cur == 1 && s[i - 1] == ' ') ||
            pre == 2) putchar(' ');
        putchar(s[i]);//输出当前字符
        pre = cur;//将当前状态保存为前一个状态，供下次循环使用
    }
    return 0;
}