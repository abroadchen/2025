//
// Created by Psy.C on 2026/9/19.
//
/**
当前的 b 可以作为所有左侧 a 的匹配对象。因为每个 b 独立，sum 加 1 表示多了一个可用的 b。相当于把当前这个 b 计入"可与左侧 a 配对的 b 池"
ans += sum：当前这个字符若作为 a，它能与右侧所有 b 组成 ab 子序列，所以 ans 增加 sum（右侧 b 的总方案）。
sum *= 2：当前字符若为 通配 ?，它可能是 a 也可能是 b（两种选择）。若作 b，则给右侧 b 池新增一份等价于整个已有 b 池的方案——所以 sum 翻倍；若作 a，已在上一步计入 ans。
注意：这里 sum *= 2 与 ans += sum 的 sum 是旧值（翻倍前）。顺序上 ans += sum 用的是翻倍前的 sum，正确
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;

int main() {
    fast;
    string s; cin >> s;
    ll sum = 0, ans = 0;
    for (int i = s.size()-1; i >= 0; --i) {
        if (s[i] == 'b') sum++;
        else ans += sum, sum *= 2;
        ans %= mod; sum %= mod;
    }
    cout << ans;
    return 0;
}