//
// Created by Psy.C on 2025/11/17.
//
/*
*创建Z数组，z[i]表示s[i...n-1]与s[0...n-1]的最长公共前缀长度
l, r：维护当前最右的匹配区间[l, r]
*如果i在当前匹配区间内，利用已计算信息初始化z[i]
z[i-l]是从位置i-l开始的Z值
r-i+1是当前位置到区间右端的距离
取两者的最小值作为初始值
*暴力扩展匹配长度
继续比较s[z[i]]和s[i+z[i]]
直到不匹配或到达字符串末尾
*如果当前匹配区间超过了之前的最右区间
更新匹配区间为[l=i, r=i+z[i]-1]
 *
*cnt[i]统计Z值等于i的个数
然后计算后缀和：cnt[i]表示Z值≥i的个数
*寻找满足条件的最长前缀：
z[n-len] == len：字符串后缀长度为len的部分与前缀完全匹配
cnt[len] > 1：存在至少一个其他位置也有长度为len的匹配
这意味着找到一个既是前缀又是后缀，且在中间也出现过的子串
*如果没找到满足条件的子串，输出"Just a legend"
否则输出长度为ans的前缀

len = i + 1：当前考虑的前缀长度
n - len：字符串中对应后缀的起始位置
z[n - len]：从后缀起始位置开始，与字符串前缀的最长匹配长度

 *
 *O(n)：Z算法的线性时间复杂度
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s; int n = s.size();
    vector<int> z(n, 0);
    int l(0), r(0);
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    vector<int> cnt(n + 2, 0);
    for (int i = 0; i < n; ++i) cnt[z[i]]++;
    for (int i = n; i >= 1; --i) cnt[i] += cnt[i + 1];
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        int len = i + 1;
        if (z[n - len] == len) if (cnt[len] > 1) ans = len;
    }
    if (ans == -1) return cout << "Just a legend", 0;
    for (int i = 1; i <= ans; ++i) cout << s[i - 1];
    return 0;
}