//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
mp[s]++：记录第一组每个串出现次数
读入第二组 n 个字符串，mp[s]--。
于是 mp[s] = 第一组次数 − 第二组次数
遍历 map 的所有 value（即差值），对每个正差值累加 max(0, val)。
也就是说：只统计第一组比第二组多出来的个数之和（若某串第一组少于或等于第二组，贡献 0）。
输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

int n, ans;
string s;
map<string, int> mp;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> s; mp[s]++; }
    rep(i,n) { cin >> s; mp[s]--; }
    for (auto &val: mp | views::values)
        ans += max(0, val);
    cout << ans << '\n';
    return 0;
}