//
// Created by Psy.C on 2026/9/13.
//
/**
循环 i 从 0 到 l/2+1（约到中点为止），每次检查：右侧第 i 位 str[l-i-1] 是否等于 s[左侧第 i 位数字]；
只要有一位不匹配就输出 No，全部匹配输出 Yes
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[] = {
    '8','x','x','3','6','9','4','7','0','5'
};
string str;
int main() {
    fast;
    cin >> str;
    int l = str.length();
    for (int i = 0; i < l/2+1; ++i) {
        if (str[l-i-1] != s[str[i]-'0']) {
            cout << "No"; return 0;
        }
    }
    cout << "Yes";
    return 0;
}