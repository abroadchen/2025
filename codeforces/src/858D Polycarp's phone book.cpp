//
// Created by Psy.C on 2026/10/1.
//
/**
a[1..n] 存 n 个字符串（每个长 9）。
mp：统计"某个子串出现在多少个不同的原字符串中"。
外层遍历每个字符串 s。
len 从 1 到 9 枚举子串长度（字符串长 9，子串最长 9）。
x 从 0 到 9 - len 枚举子串起点，substr(x, len) 取出该子串。
f（每串每长度的局部 map）用来去重：同一个字符串内相同的子串只统计一次——因为 mp[sub] 的语义是"该子串在多少个不同字符串里出现过"，同一串里重复出现也只算 1 次。
符合条件的子串直接 mp[sub]++。
注：f.clear() 在 len 循环开头调用其实多余（每次新建 map），但无害。

潜在隐患：map<string,bool> f 在 len 外层新建、len 内层使用——但 f 在 len 循环外声明（map f; f.clear(); 在 len 内），所以每换一个 len 会 clear 一次，去重范围是"同串同长度"，这是对的（同一子串在不同长度下是不同子串）
对每个字符串 s，再次按 len 从小到大、起点 x 从左到右枚举所有子串。
一旦找到 mp[sub] == 1（该子串在全局只出现一次，即只属于当前串），立即输出并 goto end 跳出这个串的处理。
len 从小到大保证：第一个找到的一定是最短的独占子串，符合"最短"要求。
若该串没有独占子串（理论上有，因为串本身长为 9，其完整子串通常独一无二），则什么也不输出（end: 空标号）
每个串有子串总数 ≈ 9+8+…+1 = 45 个，n 个串约 45n 次操作，unordered_map 均摊 O(1)，总体高效。N=1e6 足够容纳 a[]，但实际 n 远小于此即可
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+10;
string a[N];
unordered_map<string, int> mp;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        string s = a[i];
        for (int len = 1; len <= 9; ++len) {
            map<string, bool> f; f.clear();
            for (int x = 0; x + len <= 9; ++x) {
                string sub = s.substr(x, len);
                if (!f[sub]) {
                    mp[sub]++;
                    f[sub] = true;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        string s = a[i];
        for (int len = 1; len <= 9; ++len) {
            for (int x = 0; x + len <= 9; ++x) {
                string sub = s.substr(x, len);
                if (mp[sub] == 1) {
                    cout << sub << '\n';
                    goto end;
                }
            }
        }
        end:;
    }
    return 0;
}