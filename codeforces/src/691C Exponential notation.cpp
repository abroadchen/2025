//
// Created by Psy.C on 2026/4/16.
//

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e6+5;

char str[N];
int l = 1, r;
int get(char ch) {//在区间[l,r]中查找字符ch
    for (int i = l; i <= r; ++i) {
        if (str[i] == ch) return i;
    }
    return EOF;//没找到返回EOF
}

int main() {
    //读取一行字符串，存储到str[1]开始的位置（跳过str[0]）
    gets(str + 1); r = strlen(str + 1);
    int pt = get('.');//小数点位置
    for (; str[l] == 48; ++l) {}//跳过前导零
    for (; ~pt && str[r] == 48; --r) {}//如果存在小数点(~pt为真)，去除尾随零
    if (str[r] == '.') r--;//如果最后字符是小数点，将其去除
    if (str[l] == '.') {//第一位是小数点（纯小数形式）
        int e = -1, pos = l + 1;//指数初始化为-1，pos从小数点后一位开始
        for (; str[pos] == '0'; ++pos, --e) {}//跳过小数点后的零，同时减少指数
        putchar(str[pos]);
        if (pos != r) {
            putchar('.');
            for (int i = pos+1; i <= r; ++i)
                putchar(str[i]);
        }
        printf("E%d", e);//输出科学计数法表示的小数
        return 0;
    }
    //如果有小数点则指数是小数点位置-1-l，否则是r-l
    int e = (~pt ? pt - 1 : r) - l, t = r;
    for (; t > l && str[t] == 48; --t) {}//去除尾随零
    putchar(str[l]);//输出第一位数字
    if (e && t > l) putchar('.');//如果有指数且还有其他数字，输出小数点
    for (int i = l+1; i <= t; ++i)//输出其余数字（跳过原小数点）
        if (str[i] != '.' || !e) putchar(str[i]);
    if (e) printf("E%d", e);//输出指数部分
    return 0;
}