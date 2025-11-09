//
// Created by Psy.C on 2025/11/9.
//
/*
*如果标志f为false且当前字符是'0'，计数器加1
这处理的是尾部的0（第一个遇到的0）
*如果标志f为true且当前字符是'0'，计数器加2
这处理的是中间的0（在遇到1之后的0）
*如果当前字符是'1'且不是第一个字符，计数器加1，并设置标志f为true
这标记了第一次遇到'1'
*如果当前字符是'1'且已经遇到过'1'（f为true），计数器加2
这处理后续的'1'
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; getline(cin, s);
    bool f(0);
    int cnt(0);

    for (int i = s.size() - 1; i >= 0; --i) {
        if (!f && s[i] == '0') ++cnt;
        else if (f && s[i] == '0') cnt += 2;
        else if (s[i] == '1' && i > 0) { ++cnt; f = 1; }
        else if (s[i] == '1' && f == 1) cnt += 2;
    }
    printf("%d\n", cnt);
    return 0;
}