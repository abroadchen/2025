//
// Created by Psy.C on 2026/9/23.
//
/**
scanf("\n")：吃掉后面的一个换行符，保证接下来的 getchar() 从下一行开始读。
每次读取一个字符 a（getchar 可能读到 EOF，这里假定只在标准输入遇到换行时终止）。
分三种情况：
读到换行 '\n'：输出当前的 ans（连续 1 的个数），终止循环。
字符是 '1'：ans++，累加连续 1 的个数。
其他字符（比如 '0'）：先输出当前的 ans，然后把 ans 清零，重新开始计数。
输出一个换行，然后整个程序返回 0（这个写法靠 &&0 保证函数返回 0，printf 返回输出字符数作为副作用）
 */
#include <bits/stdc++.h>
using namespace std;

char a;
int main() {
    int n, ans(0); cin >> n; scanf("\n");
    while (true) {
        a = getchar();
        if (a == '\n') { printf("%d", ans); break; }
        if (a == '1') ++ans;
        else printf("%d", ans), ans = 0;
    }
    return printf("\n")&&0;
}