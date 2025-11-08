//
// Created by Psy.C on 2025/10/15.
//
/*
 *cin.ignore(): 忽略换行符
 *
 *
*如果p以s为前缀，则更新ans：
如果ans仍为空，则ans设为p
否则ans设为ans和p中字典序较小的那个
 *
 *
*输出结果：
如果ans仍为空（没有找到匹配的前缀字符串），则输出原始前缀s
否则输出找到的字典序最小的匹配字符串ans
 */
#include <algorithm>
#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string s; getline(cin, s);
    int n; cin >> n; cin.ignore();
    string ans("");
    for (int i = 0; i < n; ++i) {
        string p; getline(cin, p);//读取下一个候选字符串
        if (p.substr(0, s.size()) == s)//检查p的前s.size()个字符是否与s相同，即检查p是否以s为前缀
            ans = ("" == ans ? p : min(ans, p));
    }
    cout << ("" == ans ? s : ans) << "\n";
    return 0;
}