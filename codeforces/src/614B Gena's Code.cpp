//
// Created by Psy.C on 2026/3/24.
//
/**
判断字符串是否为"1"后面跟若干个"0"
如果不是以"1"开头，返回0
如果开头后有非"0"字符，返回0
否则返回"0"的个数（即字符串长度-1）
n: 字符串数量
s[N]: 存储输入的字符串
nz: 存储非"10...0"形式的第一个字符串
v: 存储非"1"的字符串

读入字符串数量n和所有字符串
如果有任何字符串是"0"，直接输出"0"并退出
将所有非"1"的字符串加入向量v

重置n为0
遍历所有非"1"的字符串：
如果get(i)返回0（不是"10...0"形式）且nz为空，则将其存入nz
否则将返回值（"0"的个数）累加到n
如果没有非"10...0"形式的字符串，输出"1"
否则输出第一个非"10...0"形式的字符串
输出n个"0"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int get(string s) {
    if (s[0] != '1') return 0;
    for (int i = 1; i < s.size(); ++i)
        if (s[i] != '0') return 0;
    return s.size() - 1;
}

int n;
string s[N], nz;
vector<string> v;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) {
        if (s[i] == "0") {
            cout << "0";
            return 0;
        }
        if (s[i] != "1") v.push_back(s[i]);
    }
    n = 0;
    for (const auto& i : v) {
        if (int x = get(i); !x && nz.empty()) nz = i;
        else n += x;
    }
    if (nz.empty()) cout << 1; else cout << nz;
    for (int i = 1; i <= n; ++i) cout << '0';
    return 0;
}