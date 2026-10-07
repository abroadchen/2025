//
// Created by Psy.C on 2026/10/7.
//
/**
给定字符串 s，要求把 s 重新排列，拆成若干个回文串，使回文串数量最少，并输出其中一种划分
v：所有出现次数为奇数的字符，各取一个（每个只能贡献 1 个）。
v1：字符的成对部分（每对可放在一个回文串的左右两侧）
全部字符都是偶数次 → 整个 s 本身可以排成一个大回文串，输出 1
目标是让最终回文串个数 = v.size()（奇数中心个数）。
若成对串 v1 的数量不能被 v.size() 整除，就不断从 v1 取一对，拆成两个奇数中心（各放在不同回文串中间），直到能整除。
这一步确保每个回文串恰好有一个奇数中心，且两侧的成对字符能均分
len = n / v.size()：每个回文串的目标长度。
对每个回文串：取 len/2 个成对字符作前半，中间放一个奇数中心字符，再放下半（前半反转）——构成回文
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string s, ans;
map<char, int> mp;
vector<char> v, v1;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) mp[s[i]]++;//统计每个字符出现次数
    for (char i = '0'; i <= 'z'; ++i) {
        if (!mp[i]) continue;
        if (mp[i]&1) { v.push_back(i); mp[i]--; }
        while (mp[i]) { v1.push_back(i); mp[i] -= 2; }
    }
    if (v.empty()) {
        cout << 1 << '\n';
        for (int i = 0; i < n/2; ++i) ans += v1[i];
        cout << ans;
        ranges::reverse(ans);
        cout << ans << '\n';
        return 0;
    }
    while (v1.size()%v.size()) {
        v.push_back(v1.back());
        v.push_back(v1.back());
        v1.pop_back();
    }
    cout << v.size() << '\n';
    int len = n/v.size();
    while (!v.empty()) {
        ans = "";
        for (int i = 0; i < len/2; ++i) {
            ans += v1.back();
            v1.pop_back();
        }
        cout << ans;
        cout << v.back(); v.pop_back();
        ranges::reverse(ans);
        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}