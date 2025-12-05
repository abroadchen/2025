//
// Created by Psy.C on 2025/12/5.
//
/*
 *
*初始化字符变量c为'a'
遍历字符串中的每个字符
如果当前字符比c大，则更新c为当前字符
最终c存储字符串中的最大字符（按ASCII码比较）
 *
*遍历字符串中的每个字符
如果字符等于之前找到的最大字符c，则输出该字符
 *时间复杂度：O(n)，需要遍历字符串两次 空间复杂度：O(1)，只使用了常数额外空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    char c = 'a';
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] > c) c = s[i];
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == c) cout << s[i];
    }
    return 0;
}