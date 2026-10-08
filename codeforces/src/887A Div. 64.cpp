//
// Created by Psy.C on 2026/10/8.
//
/**
找到字符串中第一个字符 1 出现的位置并返回其下标。若没有 1，return i 会返回 s.size()（循环正常结束后的 i），从而跳过整个主循环
主函数从第一个 1 的位置开始向后遍历：
遇到 0 就 ans++；
一旦 ans 达到 6，立即输出 "yes" 并结束；
遍历完还没到 6，输出 "no"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int get(const string &s) {
    for (int i = 0; i < s.size(); ++i)
        if (s[i] == '1') return i;
}

string s;
int main() {
    fast;
    cin >> s;
    int ans = 0;
    for (int i = get(s); i < s.size(); ++i) {
        if (s[i] == '0') ans++;
        if (ans == 6) { cout << "yes"; return 0; }
    }
    cout << "no";
    return 0;
}