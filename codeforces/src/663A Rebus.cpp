//
// Created by Psy.C on 2026/4/11.
//
/**
a[N]: 字符数组存储输入表达式
b[N]: 整数数组存储未知值的符号
使用gets读取输入表达式字符串
len: 输入字符串的长度
cnt: 未知项的数量计数器
pos: 等号的位置
now: 当前运行总和（从1开始）
b[0] = 1: 初始化第一项为正数
解析表达式以提取运算符
在b数组中记录每个未知项的符号
根据运算符更新运行总和now
记录等号的位置

提取等号后的目标值
将字符数字转换为整数
调整值以匹配目标
如果now < n且当前项为正数，则同时递增now和该项
如果now > n且当前项为负数，则同时递减now和该项
这些调整受限制条件约束
如果调整后，总和仍不匹配目标，输出"Impossible"
如果解决方案存在，输出"Possible"
打印原始表达式，将'?'替换为b数组中的绝对值
使用abs(b[j++])将符号转换回正值显示
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3;
char a[N];
int b[N];
int main() {
    fast;
    gets(a); int len = strlen(a);
    int cnt = 1, pos = 0, now = 1; b[0] = 1;
    for (int i = 0; i < len; ++i) {
        if (a[i] == '+') { b[cnt++] = 1; now++; }
        if (a[i] == '-') { b[cnt++] = -1; now--; }
        if (a[i] == '=') { pos = i; break; }
    }
    int n = 0;
    for (int i = pos+1; i < len; ++i) {
        if (a[i] <= '9' && a[i] >= '0')
            n = n*10 + a[i] - '0';
    }
    for (int i = 0; i < cnt; ++i) {
        while (now < n && b[i] < n && b[i] > 0)
            now++, b[i]++;
        while (now > n && b[i] > -n && b[i] < 0)
            now--, b[i]--;
    }
    if (now != n) {
        cout << "Impossible\n";
        return 0;
    }
    cout << "Possible\n";
    int j = 0;
    for (int i = 0; i < len; ++i) {
        if (a[i] != '?') printf("%c", a[i]);
        else printf("%d", abs(b[j++]));
    }
    cout << '\n';
    return 0;
}