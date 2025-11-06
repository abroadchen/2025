//
// Created by Psy.C on 2025/11/6.
//
/*
*如果结果字符串为空，或者
结果字符串的最后一个字符不等于当前字符
 *将当前字符添加到结果字符串末尾
*如果结果字符串末尾字符与当前字符相同，则删除末尾字符
这实现了"消除相邻相同字符"的效果
 *时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; getline(cin, s);
    string res("");

    for (int i = 0; i < s.size(); ++i) {
        if (res.empty() || res.back() != s[i]) res += s[i];
        else res.pop_back();
    }
    cout << res << endl;
    return 0;
}