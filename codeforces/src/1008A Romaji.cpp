//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
判断一个字符是否为英文字母中的元音：a e i o u。
注意这里没有包含 y，也没有包含 'n'。
返回 true 表示是元音，否则返回 false
读入整个字符串 s（无需空格，一行输入）
遍历 s 的每一个下标 i（0 到 s.size()-1）
!check(s[i])：当前字符不是元音。
&& s[i] != 'n'：并且当前字符不是字母 n。
合起来：当前字符是"辅音且非 n"（称为"受限辅音"）。
只有这种字符才要求后面必须跟元音；元音和 n 不受约束
对受限辅音，要求紧跟一个元音。检查它的后继字符 s[i+1]：
i+1 >= s.size()：它是最后一个字符，后面没有字符可跟 → 违规。
!check(s[i+1])：后面那个字符不是元音 → 违规。
任一情况成立，就输出 NO 并提前结束程序（return 0）
所有受限辅音后面都成功跟了元音，输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

bool check(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    return false;
}

string s;
int main() {
    fast;
    cin >> s;
    rep(i,s.size()) {
        if (!check(s[i]) && s[i] != 'n') {
            if (i+1 >= s.size() || !check(s[i+1])) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}