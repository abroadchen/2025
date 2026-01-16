//
// Created by Psy.C on 2026/1/16.
//
/**
* 递增计数: 每遇到一个'T'，理想情况下希望序列长度+1
连续性保证: 确保答案单调不减
与cnt比较: max(ans + 1, cnt) 选择当前更有利的策略
ans + 1: 基于之前序列的延续
cnt: 基于'M'字符的累积
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    char s[N]; cin >> s;
    int x = 0;
    const int n = static_cast<int>(strlen(s));
    for (; s[x] == 'F'; ++x) {}//跳过字符串开头的所有'F'字符
    int ans = 0, cnt = 0;
    for (int i = x; i <= n - 1; ++i) {
        if (s[i] == 'M') ++cnt;//当前字符是'M'
        else ans = max(ans + 1, cnt);
    }
    cout << ans << '\n';
    return 0;
}