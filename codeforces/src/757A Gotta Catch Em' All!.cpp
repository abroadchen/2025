//
// Created by Psy.C on 2026/9/3.
//
/**
s 存放输入串，mp 是字符到频次的映射
从下标 1 开始读入，统计每个字符出现的次数存到 mp 中
词 "Bulbasaur" 的字母构成是 B,u,l,b,a,s,a,u,r，其中 'u' 出现 2 次、'a' 出现 2 次，其余字母各 1 次。
所以要拼出一个完整的 "Bulbasaur"，每份需要 2 个 u 和 2 个 a，因此把 u、a 的可用次数折半
遍历 "Bulbasaur" 的每个字母，取所有字母中可用次数的最小值 mn。这就是木桶效应——能拼出的单词数受最缺的那个字母限制
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10, inf = 21e8;
char s[N];
map<char, int> mp;
int main() {
    fast;
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) mp[s[i]]++;
    mp['u'] /= 2; mp['a'] /= 2;
    string s2 = "Bulbasaur";
    int mn = inf; len = s2.size();
    for (int i = 0; i <= len-1; ++i)
        mn = min(mn, mp[s2[i]]);
    cout << mn << '\n';
    return 0;
}