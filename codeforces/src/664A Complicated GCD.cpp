//
// Created by Psy.C on 2026/4/11.
//
/**
使用strlen获取两个字符串的长度
如果长度相等，比较每个字符位置
如果字符串完全相同，返回1；否则返回0
如果长度不同，立即返回0

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;

char s1[N], s2[N];
int check() {
    int l1 = strlen(s1), l2 = strlen(s2);
    if (l1 == l2) {
        for (int i = 0; i < l1; ++i)
            if (s1[i] != s2[i])
                return 0;
        return 1;
    }
    return 0;
}

int main() {
    fast;
    cin >> s1 >> s2;
    if (check()) cout << s1 << '\n';
    else cout << "1\n";
    return 0;
}