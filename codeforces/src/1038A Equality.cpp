//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
遍历前 k 个大写字母（'A' 到 'A'+k-1）：
只要有一个没出现过（mp == 0），直接输出 0 并结束。
否则更新 ans 为这些计数中的最小值

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int inf = 0x3f3f3f3f;

int n, k;
string s;
map<char,int> mp;
int main() {
    fast;
    cin >> n >> k >> s;
    int ans = inf;
    for (int i = 0; i < n; i++)
        if (s[i] <= k+'A') mp[s[i]]++;
    for (int i = 0; i < k; i++) {
        if (mp[i+'A'] == 0) { cout << "0\n"; return 0; }
        ans = min(ans, mp[i+'A']);
    }
    cout << ans*k << '\n';
    return 0;
}