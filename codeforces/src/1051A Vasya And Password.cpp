//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
t：测试组数；
c1：数字字符（'0'-'9'）个数；
c2：小写字母（'a'-'z'）个数；
c3：大写字母（'A'-'Z'）个数——但注意本分类里把"既非数字又非小写"的都归为 c3，通常假定输入只有这三类；
s：当前字符串
保证有数字（c1）
数字个数为 0 时：
找一个小写字母且小写总数 c2 ≥ 2（改掉一个小写仍至少剩 1 个小写），把它改成 '0'，c1++、c2--；
否则找一个大写字母且 c3 ≥ 2，改成 '0'，c1++、c3--。
只要 c1 变成 1 就退出循环（&& !c1）
保证有小写（c2）
小写个数为 0 时：从数字（c1≥2）‍或大写（c3≥2）‍里借一个改成 'a'。
保证有大写（c3）
大写个数为 0 时：从数字（c1≥2）‍或小写（c2≥2）‍里借一个改成 'A'
每行输出修正后的字符串。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int t, c1, c2, c3;
string s;
int main() {
    fast;
    cin >> t;
    while (t--) {
        cin >> s; c1 = c2 = c3 = 0;
        for (char i : s) {
            if (i >= '0' && i <= '9') c1++;
            else if (i >= 'a' && i <= 'z') c2++;
            else c3++;
        }
        if (!c1) {
            for (int i = 0; i < s.size() && !c1; i++) {
                if (s[i] >= 'a' && s[i] <= 'z' && c2 >= 2)
                    s[i] = '0', c1++, c2--;
                else if (s[i] >= 'A' && s[i] <= 'Z' && c3 >= 2)
                    s[i] = '0', c1++, c3--;
            }
        }
        if (!c2) {
            for (int i = 0; i < s.size() && !c2; i++) {
                if (s[i] >= '0' && s[i] <= '9' && c1 >= 2)
                    s[i] = 'a', c2++, c1--;
                else if (s[i] >= 'A' && s[i] <= 'Z' && c3 >= 2)
                    s[i] = 'a', c2++, c3--;
            }
        }
        if (!c3) {
            for (int i = 0; i < s.size() && !c3; i++) {
                if (s[i] >= '0' && s[i] <= '9' && c1 >= 2)
                    s[i] = 'A', c3++, c1--;
                else if (s[i] >= 'a' && s[i] <= 'z' && c2 >= 2)
                    s[i] = 'A', c3++, c2--;
            }
        }
        cout << s << '\n';
    }
    return 0;
}