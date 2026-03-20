//
// Created by Psy.C on 2026/3/21.
//
/**
s: 存储输入的原始字符串
a: 存储合法数字的字符串，初始化为开始引号"
b: 存储非法数据的字符串，初始化为开始引号"
t: 临时字符串，用于构建当前正在处理的token
flag: 标志位，用于判断当前token是否为合法整数

遍历输入字符串中的每个字符
检查当前字符是否为分隔符（逗号或分号）
如果临时字符串非空且标记为合法整数且不以0开头（除非只有单个0）
将临时字符串添加到合法结果字符串a，并添加逗号
否则将临时字符串添加到非法结果字符串b，并添加逗号
清空临时字符串
重置标志位为true
如果不是分隔符，将当前字符添加到临时字符串t
如果遇到小数点，则设置flag为false（表示不是整数）
如果遇到非数字字符，则设置flag为false
如果临时字符串还有内容（即最后一个token）
根据合法性将其添加到对应的结果字符串中

如果原字符串以分隔符结尾，在b后添加逗号
如果a以逗号结尾，将最后一个逗号替换为结束引号
否则将a设为"-"（表示没有合法整数）
对b执行相同的操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s, a = "\"", b = "\"", t;
bool flag = true;
int main() {
    fast;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ',' || s[i] == ';') {
            if (t.size() && flag && (t[0] != '0' || t.size() == 1)) {
                a += t; a += ",";
            } else {
                b += t; b += ",";
            }
            t = "";
            flag = true;
        } else {
            t += s[i];
            if (s[i] == '.') flag = false;
            if (!(s[i] >= '0' && s[i] <= '9')) flag = false;
        }
    }
    if (t.size()) {
        if (flag && (t[0] != '0' || t.size() == 1)) {
            a += t; a += ",";
        } else {
            b += t; b += ",";
        }
    }
    if (s[s.size()-1] == ',' || s[s.size()-1] == ';') b += ",";
    if (a[a.size()-1] == ',') a[a.size()-1] = '\"'; else a = "-";
    if (b[b.size()-1] == ',') b[b.size()-1] = '\"'; else b = "-";
    cout << a << '\n' << b << '\n';
    return 0;
}