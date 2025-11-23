//
// Created by Psy.C on 2025/11/21.
//
/*
 *s:结果字符串, t:输入字符串
 *n:输入字符串长度, a:空格标记（0表示上一个字符不是空格，1表示是空格）
 *
 *时间复杂度：O(n)，其中n是输入字符串长度 空间复杂度：O(n)
 */
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s, t; getline(cin, t); int n = (int)t.size(), a = 0;
    for (int i = 0; i < n; ++i) {
        if (isalpha(t[i])) { s.push_back(t[i]); a = 0; }//标记上一个字符不是空格
        else if (t[i] == ' ' && a == 0) { s.push_back(' '); a = 1; }//如果当前字符是空格且上一个字符不是空格
        else if (t[i] == '.' || t[i] == ',' || t[i] == '?' ||
            t[i] == ';' || t[i] == ':' || t[i] == '"' || t[i] == '!') {
            if (a == 1) s.pop_back();//如果上一个字符是空格，则删除这个空格（标点前不保留空格）
            s.push_back(t[i]);//添加标点符号
            s.push_back(' ');//在标点后添加空格
            a = 1;//标记上一个字符是空格
        }
    }
    cout << s;
    return 0;
}