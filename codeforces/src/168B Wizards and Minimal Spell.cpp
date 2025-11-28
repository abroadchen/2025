//
// Created by Psy.C on 2025/11/28.
//
/*
*flag: 状态标志，用于跟踪处理模式
0: 初始状态
1: 处理普通文本行
2: 处理注释行（以#开头）
i: 循环变量
s: 存储读取的每行字符串
 *
 *循环读取输入的每一行，直到文件结束
 *跳过行首的空格字符，找到第一个非空格字符的位置
*判断条件：如果行为空（全是空格）或者第一个非空格字符不是'#'
即：处理普通文本行（包括空行）
 *如果之前处理的是注释行（flag=2），则先输出一个换行符
 *输出该行中所有非空格字符（实际上输出整行，只是跳过了空格？）
 *设置标志为1，表示刚刚处理了普通文本行
 *否则：处理以'#'开头的注释行
 *如果之前处理过任何行（flag非0），则先输出一个换行符
 *直接输出整行注释内容
 *设置标志为2，表示刚刚处理了注释行
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

int main() {
    fast;
    int flag = 0, i;
    string s;
    while (getline(cin, s)) {
        for (i = 0; i < sz(s); ++i) if (s[i] != ' ') break;
        if (i == sz(s) || s[i] != '#') {
            if (flag == 2) cout << '\n';
            for (i = 0; i < sz(s); ++i) if (s[i] != ' ') cout << s[i];
            flag = 1;
        } else {
            if (flag) cout << '\n';
            cout << s;
            flag = 2;
        }
    }
    cout << '\n';
    return 0;
}