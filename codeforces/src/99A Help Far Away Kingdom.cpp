//
// Created by Psy.C on 2025/11/12.
//
/*
 *i存储小数点前一位数字，f存储小数点后一位数字
 *在找到小数点之前，将每个字符添加到s2字符串中
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    int n = s.length(), i = 0, f = 0;
    string s2;

    for (int j = 0; j < n; ++j) {
        if (s[j] == '.') {
            i = s[j - 1] - '0';
            f = s[j + 1] - '0';
            break;
        }
        s2.append(1, s[j]);
    }
    if (i == 9) { cout << "GOTO Vasilisa." << '\n'; return 0; }
    if (f < 5) { cout << s2 << '\n'; return 0; }//如果小数点后一位数字小于5，直接输出整数部分，不进行进位
    s2[s2.size() - 1] += 1;//将整数部分最后一位数字加1
    cout << s2 << '\n';
    return 0;
}