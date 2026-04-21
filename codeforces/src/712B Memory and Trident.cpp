//
// Created by Psy.C on 2026/4/20.
//
/**
s[N]：存储输入的移动指令字符串
len：字符串实际长度
a：'U'（向上）指令计数
b：'D'（向下）指令计数
c：'L'（向左）指令计数
d：'R'（向右）指令计数
持续读取输入字符串直到结束
如果字符串长度为奇数，直接输出-1
原因：要回到原点，需要成对的相反移动，所以总步数必须是偶数
遍历字符串，统计四个方向的移动次数
abs(a - b)：上下方向不平衡的步数
abs(c - d)：左右方向不平衡的步数
(abs(a-b) + abs(c-d))/2：需要修改的最少指令数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+7;
char s[N];
int len;
int main() {
    fast;
    int a = 0, b = 0, c = 0, d = 0;
    while (cin >> s) {
        len = strlen(s);
        if (len % 2 == 1) cout << "-1\n";
        else {
            for (int i = 0; s[i] != '\0'; ++i) {
                if (s[i] == 'U') a++;
                else if (s[i] == 'D') b++;
                else if (s[i] == 'L') c++;
                else if (s[i] == 'R') d++;
            }
            cout << (abs(a - b) + abs(c - d))/2 << '\n';
            a = b = c = d = 0;
        }
    }
    return 0;
}