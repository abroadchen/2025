//
// Created by Psy.C on 2025/11/17.
//
/*
n：字符串长度
lev：当前缩进级别（层级）
i：当前处理位置的索引*
 *
循环处理整个字符串，直到处理完所有字符
如果当前字符是'<'，说明遇到了标签开始*
 *检查是否为结束标签（以"</"开始）
*提取4个字符作为标签内容（应该是"</a>"这样的格式）
处理位置向前移动4位
缩进级别减1（因为是结束标签）
输出相应数量的空格进行缩进（每级2个空格）
输出标签内容并换行
 *
*提取3个字符作为标签内容（应该是"<a>"这样的格式）
处理位置向前移动3位
输出相应数量的空格进行缩进（每级2个空格）
输出标签内容并换行
缩进级别加1（因为是开始标签）
 *
 *
 *
 */
#include <string>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    int n = s.length(), lev = 0, i = 0;
    while (i < n) {
        if (s[i] == '<') {
            if (i + 1 < n && s[i + 1] == '/') {
                string t = s.substr(i, 4);
                i += 4;
                lev--;
                for (int j = 0; j < 2 * lev; ++j) cout << ' ';
                cout << t << '\n';
            } else {
                string t = s.substr(i, 3);
                i += 3;
                for (int j = 0; j < 2 * lev; ++j) cout << ' ';
                cout << t << '\n';
                lev++;
            }
        }
    }
    return 0;
}