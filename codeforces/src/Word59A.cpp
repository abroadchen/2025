//
// Created by Psy.C on 2025/10/26.
//
/*
 *声明整型变量l并初始化为0，用于统计小写字母数量
*遍历字符串中的每个字符
使用islower函数判断字符是否为小写字母
如果是小写字母，则计数器l加1
 *
 *声明一个函数指针f，指向接受int参数并返回int的函数
*判断小写字母数量是否占总字符数的一半或以上
如果是，则将函数指针f指向tolower函数（转小写）
否则指向toupper函数（转大写）
*遍历字符串中的每个字符
使用函数指针f所指向的函数（tolower或toupper）处理每个字符
 *输出处理后的字符串
 *
 *
 */
#include <cctype>
#include <ios>
#include <iostream>
#include <string>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string s; getline(cin, s);
    int l(0);
    for (int i = 0; i < s.size(); ++i) {
        if (islower(s[i])) l++;
    }
    int (*f)(int);
    if (l >= 1.0 * s.size() / 2) f = tolower;
    else f = toupper;

    for (int i = 0; i < s.size(); ++i) {
        s[i] = f(s[i]);
    }
    cout << s << endl;
    return 0;
}