//
// Created by Psy.C on 2025/10/11.
//
/*
*判断Father是否获胜的条件：
t[0] != t[1]：Father的选择与Mother不同
t[1] == t[2]：Mother和Son选择相同
(3 + t[0] - t[1]) % 3 == 1：Father的选择能战胜Mother的选择
这里使用模运算判断胜负关系：(差值+3)%3 == 1表示前者战胜后者
rock(0)战胜scissors(2)：(0-2+3)%3 = 1
paper(1)战胜rock(0)：(1-0+3)%3 = 1
scissors(2)战胜paper(1)：(2-1+3)%3 = 1
如果满足条件，输出"F"表示Father获胜
 *
*判断Mother是否获胜的条件：
t[1] != t[0]：Mother的选择与Father不同
t[0] == t[2]：Father和Son选择相同
(3 + t[1] - t[2]) % 3 == 1：Mother的选择能战胜Son的选择
如果满足条件，输出"M"表示Mother获胜
 *
*判断Son是否获胜的条件：
t[2] != t[0]：Son的选择与Father不同
t[0] == t[1]：Father和Mother选择相同
(3 + t[2] - t[0]) % 3 == 1：Son的选择能战胜Father的选择
如果满足条件，输出"S"表示Son获胜
 *
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {

    int t[3] = {0};
    for (int i = 0; i < 3; ++i) {
        string s; getline(cin, s);
        if (s[0] == 'r') t[i] = 0;
        else if (s[0] == 'p') t[i] = 1;
        else if (s[0] == 's') t[i] = 2;
    }

    if (t[0] != t[1] && t[1] == t[2] && (3 + t[0] - t[1]) % 3 == 1) puts("F");
    else if (t[1] != t[0] && t[0] == t[2] && (3 + t[1] - t[2]) % 3 == 1) puts("M");
    else if (t[2] != t[0] && t[0] == t[1] && (3 + t[2] - t[0]) % 3 == 1) puts("S");
    else puts("?");
    return 0;
}