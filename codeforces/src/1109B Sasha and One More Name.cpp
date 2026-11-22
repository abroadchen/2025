//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
只需扫前半段 [1, size/2)，若发现某个字符与 s[0] 不同就返回 1（说明存在不同字符）。
返回 1 = "字符不全都一样"；返回 0 = "所有字符全相同"
对称比较 s[i] 与 s[size-1-i]，全部相等则回文返回 1，否则返回 0。
标准回文判定
复制 t = s。
循环 s.size() 次，每次循环左移一位（t = t.substr(1) + t[0]），即把第一个字符移到末尾。
若某次旋转得到的 t 不等于原串 s 且是回文，返回 1（可行）。
所有旋转都试过仍不行，返回 0。
作用：若存在一次旋转能使其成为"非自身的回文串"，答案是 1
!check(s) 为真 → 所有字符全相同（如 "aaaa"）→ 无论如何旋转都是自身，不可能变成别的回文 → Impossible。

ok(s) 为真 → 存在一次旋转使它成为非自身回文 → 1（一次即可）。

否则 → 需要两次操作（先把字符串切成两个回文块之类）→ 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

bool check(const string &s) {
    for (int i = 1; i < s.size()/2; i++)
        if (s[i] != s[0]) return 1;
    return 0;
}
bool chk(const string &s) {
    rep(i, s.size()/2) if (s[i] != s[s.size()-i-1]) return 0;
    return 1;
}
bool ok(const string& s) {
    string t = s;
    rep(i,s.size()) {
        t = t.substr(1) + t[0];
        if (t != s && chk(t)) return 1;
    }
    return 0;
}

string s;
int main() {
    fast;
    cin >> s;
    if (!check(s)) cout << "Impossible\n";
    else if (ok(s)) cout << 1 << '\n';
    else cout << 2 << '\n';
    return 0;
}