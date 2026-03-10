//
// Created by Psy.C on 2026/3/9.
//
/**
要找到"AB"和"BA"两个子串，且不重叠，至少需要4个字符
a = s.find("AB")：找到第一个"AB"的位置
b = s.find("BA", a+2)：从a+2位置开始找"BA"（确保不与"AB"重叠）
c = s.find("BA")：找到第一个"BA"的位置
d = s.find("AB", c+2)：从c+2位置开始找"AB"（确保不与"BA"重叠）
如果能找到不重叠的"AB"和"BA"（两种可能的顺序）：
"AB"在前，"BA"在后（a和b都存在）
或"BA"在前，"AB"在后（c和d都存在）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    if (s.size() <= 3) cout << "NO\n";
    else {
        int a = s.find("AB"), b = s.find("BA", a+2),
        c = s.find("BA"), d = s.find("AB", c+2);
        if (a != -1 && b != -1 || c != -1 && d != -1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}