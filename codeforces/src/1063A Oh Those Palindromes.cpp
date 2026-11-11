//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
n：字符串长度；
s：读入的字符串
a[i] 表示字母 i+'a'（即第 i 个小写字母）出现的次数。
遍历字符串每个字符 s[i]，用 s[i]-'a' 把字符映射成 0-25 的下标，然后 a[该下标]++。
这里就是字母频次统计，标准桶计数写法
i 从 0 到 30，即从 'a' 遍历到 'a'+30；
若 a[i] != 0（该字母出现过），就把它输出 a[i] 次
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 50;

int n, a[N];
string s;
int main() {
    fast;
    cin >> n >> s;
    rep(i,n) a[s[i]-'a']++;
    rep(i,31) {
        char x = i + 'a';
        if (a[i] != 0)
            for (int j = 1; j <= a[i]; j++)
                cout << x;
    }
    return 0;
}