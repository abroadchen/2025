//
// Created by Psy.C on 2026/4/1.
//
/**
a[2] = b[1], a[3] = b[0]: 将b的第1位赋给a的第2位，b的第0位赋给a的第3位
c[2] = d[1], c[3] = d[0]: 将d的第1位赋给c的第2位，d的第0位赋给c的第3位
i, j: 用于追踪a和c中当前比较位置
flag: 匹配标志，初始化为1（true）
找到a中'A'的位置，赋值给i
找到c中'A'的位置，赋值给j
循环4次（每个字符串长度为4）
每次循环后i和j都向右移动一位（模4循环）
如果a[i] == 'X'，跳过这个位置（移动到下一个）
如果c[j] == 'X'，跳过这个位置（移动到下一个）
如果对应位置字符不相等，设置flag为0（false）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 11;
char a[N], b[N], c[N], d[N];
int main() {
    fast;
    cin >> a >> b >> c >> d;
    a[2] = b[1], a[3] = b[0], c[2] = d[1], c[3] = d[0];
    int i = 0, j = 0, flag = 1;
    while (a[i] != 'A') i++;
    while (c[j] != 'A') j++;
    for (int k = 0; k < 4; ++k, i = (i+1)%4, j = (j+1)%4) {
        if (a[i] == 'X') i = (i+1)%4;
        if (c[j] == 'X') j = (j+1)%4;
        if (a[i] != c[j]) flag = 0;
    }
    cout << (flag ? "YES" : "NO") << '\n';
    return 0;
}