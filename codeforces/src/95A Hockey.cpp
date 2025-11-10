//
// Created by Psy.C on 2025/11/10.
//
/*
*函数rep，根据原始字符串t的大小写恢复答案字符串ans的大小写：
如果t中某位置是大写字母，则将ans对应位置转换为大写（减32）
 *
*外层循环遍历ans的每个位置l
内层循环检查每个模式字符串s[i]
从位置l截取与s[i]等长的子串x
如果x与s[i]匹配，则调用f函数标记匹配位置范围
 *
*遍历答案字符串，对标记位置进行字符替换：
如果位置i被标记（ok[i]为true）
如果当前字符等于替换字符c，则替换为'a'或'b'（避免与c相同）
否则直接替换为字符c
 */
#include <iostream>
using namespace std;

const int N = 105;
string s[N], t, ans;
char c;
bool ok[N];

void f(int l, int r) { for (int i = l; i <= r; ++i) ok[i] = true; }

string to_lower(string str) {
    for (int i = 0; i < str.size(); ++i) {
        if ('A' <= str[i] && str[i] <= 'Z') str[i] += 32;
    }
    return str;
}

void rep() {
    for (int i = 0; i < t.size(); ++i) {
        if ('A' <= t[i] && t[i] <= 'Z') ans[i] -= 32;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i], s[i] = to_lower(s[i]);
    cin >> t >> c;
    ans = to_lower(t);
    for (int l = 0; l < ans.size(); ++l) {
        for (int i = 1; i <= n; ++i) {
            string x = ans.substr(l, s[i].size());
            if (x == s[i]) f(l, l + s[i].size() - 1);
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        if (ok[i]) {
            if (ans[i] == c) {
                if (c == 'a') ans[i] = 'b';
                else ans[i] = 'a';
            } else ans[i] = c;
        }
    }
    rep(), cout << ans;
    return 0;
}