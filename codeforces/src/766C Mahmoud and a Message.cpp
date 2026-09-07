//
// Created by Psy.C on 2026/9/7.
//
/**
len：字符串长度。
dp[N]：记忆化数组，存 dfs(pos) 的结果（0 表示未计算）。
p[N]：核心数组，p[i] 表示以 i 为起点能分割出的最右端位置（闭区间右端）。即 [i, p[i]] 是一个"合法段"。
num[26]：每个字母（a..z）的最大出现次数限制，对应题目限制。
s：读入的字符串

参数 pos：当前考虑从下标 pos 开始的分割。
边界：pos >= len 表示已经分完整个字符串，返回 1（一种完成方案）。
记忆化：dp[pos] 非 0 直接返回，避免重复计算。
转移：以 pos 起点的合法段是 [pos, p[pos]]，所以下一个分割起点 i 可以是 pos+1 到 p[pos]+1 的任意位置（即"从 pos 开始的这一段可以截到任意位置"）。把每种可能累加，取模。
返回值 dp[pos] = 从 pos 开始所有合法分割方案总数

对每个起点 i，找出从这个位置开始、能满足"段长不超过该段内某字母数量限制"的最长合法右端点，存入 p[i]：
内层从 j = i 向右扩展，mn 维护当前段内每个字母 num[...] 的最小值（num[c] 表示该字母允许的段长上限）。
每加入一个字符 s[j]，更新 mn = min(mn, num[s[j]-'a'])。
若当前段长 j-i+1 > mn（段长超过了某个字母的限制），说明这段不合法，记 k = j-1 并 break。
若无任何字母超限（循环走完 k 仍为 -1），则这段可以延伸到末尾，p[i] = len-1。
每处理完一个起点，重置 ch、mn = inf

输出 1（方案总数）‍：dfs(0) —— 合法分割方案数 % mod。

输出 2（最长段长）‍：mx = max(p[i]-i+1) —— 遍历找所有合法段中长度最大值（p[i]-i+1 即以 i 起的最长合法段长度）。

输出 3（最少段数）‍
从 i=0 开始，每次直接跳到以 i 为起点的最长合法段末尾 p[i]，段数 mn++，for 循环的 ++i 会让 i 从 p[i] 继续。这样用最长的合法段分割，得到最少段数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5, inf = 2e9, mod = 1e9+7;

int len, dp[N], p[N], num[26];
char s[N];
int dfs(int pos) {
    if (pos >= len) return 1;
    if (dp[pos]) return dp[pos];
    int &ans = dp[pos]; ans = 0;
    for (int i = pos+1; i <= p[pos]+1; ++i)
        ans = (dfs(i)+ans)%mod;
    return ans;
}

void init() {
    int ch[26] = {}, mn = inf;
    for (int i = 0; i < len; ++i) {
        int k = -1;
        for (int j = i; j < len; ++j) {
            mn = min(mn, num[s[j]-'a']);
            if (j-i+1 > mn) { k = j-1; break; }
        }
        p[i] = k == -1 ? len-1 : k;
        memset(ch, 0, sizeof(ch));
        mn = inf;
    }
}

int main() {
    fast;
    cin >> len >> s;
    for (int &i : num) cin >> i;
    init();
    int mx = 0;
    for (int i = 0; i < len; ++i) mx = max(mx, p[i]-i+1);
    int mn = 0;
    for (int i = 0; i < len; ++i) { i = p[i]; mn++; }
    cout << dfs(0) << '\n' << mx << '\n' << mn;
    return 0;
}