//
// Created by Psy.C on 2026/4/23.
//
/**
n：输入的行数
a[N]：存储每行应该有的元音字母数量
f = 1：标志位，初始为1（真），表示符合条件
s[N]：存储输入的字符串

循环n次，读入n行字符串
gets(s)：读入一行字符串
len = strlen(s)：获取字符串长度
num = 0：初始化元音字母计数器
遍历字符串的每个字符
统计元音字母数量（包括'a','e','i','o','u','y'）
每遇到一个元音字母，计数器num加1
如果当前行的元音字母数量不等于期望值a[i]
将标志位f设为0（表示不符合条件）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 107;


int n, a[N], f = 1;
char s[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    getchar();//读取换行符，消除cin和gets之间的缓冲区问题
    for (int i = 1; i <= n; ++i) {
        gets(s);
        int len = strlen(s), num = 0;
        for (int j = 0; j < len; ++j) {
            if (s[j] == 'a' || s[j] == 'e' || s[j] == 'i' ||
                s[j] == 'o' || s[j] == 'u' || s[j] == 'y')
                num++;
        }
        if (num != a[i]) f = 0;
    }
    if (f == 0) cout << "NO\n"; else cout << "YES\n";
    return 0;
}