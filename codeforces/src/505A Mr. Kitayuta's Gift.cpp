//
// Created by Psy.C on 2026/2/25.
//
/**
外层循环：在字符串的每个位置（包括末尾）尝试插入字符：
i从0到s.size()（共s.size()+1个位置）
!flag：一旦找到回文就停止搜索
内层循环：尝试插入每个小写字母：
j从'a'到'z'（ASCII值97到122）
!flag：一旦找到回文就停止搜索

s.substr(0, i)：原字符串前i个字符
string(1, j)：插入的单个字符
s.substr(i)：原字符串从位置i开始的剩余部分
u = t：复制字符串用于反转比较


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    bool flag = false;//是否找到了回文串
    for (int i = 0; i < s.size() + 1 && !flag; ++i)
        for (int j = 'a'; j < 'z' + 1 && !flag; ++j) {
            string t = s.substr(0, i) + string(1, j) + s.substr(i), u = t;
            ranges::reverse(u);
            if (t == u) {
                flag = true;
                cout << t << '\n';
                break;
            }
        }
    if (!flag) cout << "NA\n";
    return 0;
}