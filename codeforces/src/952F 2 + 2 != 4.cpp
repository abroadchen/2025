//
// Created by Psy.C on 2026/10/18.
//
/**
n1 = 当前累积结果, n2 = 正在读的第二个操作数
当前运算符(+/-)，初始为空格
逐字符读入，直到换行或文件尾
没有运算符 → 读第一个数到 n1
已有运算符 → 读第二个数到 n2
连续++：先算前一个+
前一个是-，先算掉，然后更新op为+
首次遇到+，仅记录op
 */
#include <bits/stdc++.h>
using namespace std;


int main() {
    char c;
    int n1 = 0, n2 = 0;
    char op = ' '; c = getchar();
    while (c != '\n' && c != EOF) {
        if (c >= '0' && c <= '9' && op == ' ') n1 = n1*10+c-'0';
        else if (c >= '0' && c <= '9') n2 = n2*10+c-'0';
        if (c == '+' && op == '+') { n1 = n1 + n2; n2 = -5; }
        else if (c == '+' && op == '-') { n1 = n1 - n2; n2 = -5; op = '+'; }
        else if (c == '+') { n2 = -5; op = '+'; }
        else if (c == '-' && op == '+') { n1 = n1 + n2; n2 = -3; op = '-'; }
        else if (c == '-' && op == '-') { n1 = n1 - n2; n2 = -3; }
        else if (c == '-') { n2 = -3; op = '-'; }
        c = getchar();
    }
    if (op == '-') n1 -= n2; else n1 += n2;
    printf("%d\n", n1);
    return 0;
}