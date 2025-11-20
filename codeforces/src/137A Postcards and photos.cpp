//
// Created by Psy.C on 2025/11/20.
//
/*
*c(1)：计数器，初始化为1，用于统计段落数量
k(1)：连续字符计数器，初始化为1，用于跟踪当前连续相同字符的个数
i：循环变量
 *
*条件判断，如果满足以下任一条件：
s[i] != s[i-1]：当前字符与前一个字符不同
k == 5：当前连续相同字符已达5个
则执行：
k = 1：重置连续字符计数器为1
c++：段落计数器加1
*如果不满足上述条件（即字符相同且连续计数未达5），则：
k++：连续字符计数器加1
 *
 */
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char s[101];
    int c(1), k(1), i;
    scanf("%s",s);
    for (i = 1; i < strlen(s); ++i) {
        if (s[i] != s[i - 1] || k == 5) { k = 1; c++; }
        else k++;
    }
    printf("%d",c);
    return 0;
}