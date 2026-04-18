//
// Created by Psy.C on 2026/4/17.
//
/**
s: 存储输入的科学计数法字符串
dl: 小数点后数字的起始位置
dr: 指数'e'的位置
b: 指数值
符号位 + 整数部分 + 小数部分 + e + 指数
O(n)，其中n是输入字符串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
char s[N];
int dl, dr, b;
int main() {
    fast;
    cin >> s; cout << s[0];//输出整数部分（通常是符号位或第一位数字）
    dl = 2;//小数点后第一位数字的位置
    int d = 0;//是否在小数部分存在非零数字
    for (dr = dl; s[dr] != 'e'; ++dr)//从位置dl开始寻找'e'
        if (s[dr] != '0' && s[dr] != 'e') d = 1;//检查是否有非零小数位
    for (int i = dr+1; s[i]; ++i)
        b = b*10 + s[i] - '0';//将指数部分转换为整数
    if (b == 0) {//指数为0
        if (d) {
            cout << '.';
            for (int i = dl; i < dr; ++i)
                cout << s[i];//输出小数部分
        }
    } else {//指数大于0
        for (int i = dl; i < min(dl+b, dr); ++i)
            cout << s[i];//输出整数部分（移动小数点后）
        if (dl + b >= dr)
            for (int i = 1; i <= b - (dr - dl); ++i)
                cout << '0';//如果指数超出小数部分长度，补0
        else if (d) {//如果有非零小数部分，继续输出小数
            cout << '.';
            for (int i = dl + b; i < dr; ++i)
                cout << s[i];
        }
    }
    return 0;
}