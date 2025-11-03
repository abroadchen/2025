//
// Created by Psy.C on 2025/11/3.
//
/*
*如果长度小于等于N(10)，直接输出原字符串
否则输出字符串的首字符 + (长度-2) + 末字符，实现字符串缩写功能
 *
 */
#include <iostream>
using namespace std;

const int N = 10;
int n, l;
string s;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    do {
        cin >> s; l = s.size();
        if (l <= N) cout  << s << endl;
        else cout << s[0] << l - 2 << s[l - 1] << endl;
    } while (--n);
    return 0;
}