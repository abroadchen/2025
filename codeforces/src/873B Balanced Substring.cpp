//
// Created by Psy.C on 2026/10/6.
//
/**
sum：当前前缀的平衡值（1 记 +1，0 记 -1）。
ans：答案，最长合法子串长度，初始为 0。
b[]：哈希表/桶，b[sum+inf] 记录某个平衡值 sum 第一次出现的位置。
inf = 1e5：因为 sum 可能是负数，统一加上 inf 作为偏移量，用 sum+inf 作为数组下标（保证下标非负
若 s[i-1]=='1'，sum++；否则 sum--（即 '0' 时减 1）。
if (sum == 0) ans = max(ans, i);
如果从头到当前位置的前缀平衡值为 0，说明整个前缀 [1..i] 本身就 0、1 数量相等，直接更新答案。
if (b[sum+inf] == 0) b[sum+inf] = i;
如果这个平衡值 sum 第一次出现，记录它的位置 i（用 0 作占位判断"未出现过"，但注意 i 从 1 开始，位置 0 不会被误判）。
else ans = max(ans, i - b[sum+inf]);
如果这个平衡值之前出现过，那么从之前那个位置的后一位到当前位置的子串平衡差值回到 0，说明这一段 0、1 数量相等。用当前位置 i 减去第一次出现的位置，得到这段长度，更新答案。
最终输出 ans，即最长的 0、1 数量相等的连续子串长度。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, inf = 1e5;

string s;//存储输入的 01 字符串
int main() {
    fast;
    int n; cin >> n >> s;
    int sum = 0, ans = 0, b[N]{};
    for (int i = 1; i <= n; ++i) {
        if (s[i-1] == '1') sum++; else sum--;
        if (sum == 0) ans = max(ans, i);
        if (b[sum+inf] == 0) b[sum+inf] = i;
        else ans = max(ans, i-b[sum+inf]);
    }
    cout << ans;
    return 0;
}