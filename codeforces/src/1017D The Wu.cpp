//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
len 最大为 12（1<<12 是 4096），N 为所有可能串（按二进制编号）的容量。
M = 20 预留（本代码未真正使用，属预留）
len：串长度。
cnt[N]：cnt[编号] = 拥有该二进制模式的样例串个数（读入时累加）。
w[M]：每一位的权重，下标 1..len。
dp[N][110]：dp[串编号][k] = 与查询串得分 ≤ k 的样例串个数（前缀和后的结果）
第一段（双层枚举 + 得分计算）‍：

外层 s1 遍历所有样例串模式，内层 s2 遍历所有可能的查询串模式。
对每一个 (s1,s2) 组合，计算"得分" ret：
内部循环 b 从 0 到 len-1：
b1 = s1 的第 b 位，b2 = s2 的第 b 位；
若 b1 == b2（该位相同）‍，则累加 w[len-b]（对应高位的权重）。
也就是说：得分 = 所有"与查询串对应位相同"的位置的权重之和。
若 ret ≤ 100，把 cnt[s1]（拥有该样例模式的样例数）累加到 dp[s2][ret] 中：即"所有与查询串 s2 得分恰好等于 ret 的样例总数"。
第二段（对得分维度做前缀和）‍：

dp[s][j] += dp[s][j-1]，把"恰好得分 = j"累加成"得分 ≤ j"。
这样就得到最终语义：dp[s][k] = 与查询串 s 得分 ≤ k 的样例串总数
把字符串 s（例如 "1010"）解析成整数编号：第 j 位若为 '1'，则加上 2^(len-1-j)（即按高位在左的二进制位权计算）。
用于把样例串/查询串统一映射成数组下标。
读入 len, n, q；读入 len 个权重 w[i]。
读入 n 个样例串，用 get 转编号并在 cnt[] 计数。
调用 init() 预处理所有可能的查询串对应的 DP 前缀和。
处理 q 次查询：每次读入查询串和阈值 k，直接输出 dp[get(s)][k]（得分 ≤ k 的样例数），O(1) 查表
复杂度：预处理 O(2^len × 2^len × len + 2^len × 100)，查询 O(len)（仅取编号及一次查表）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
#define For(i,n) for (int i=1; i<=n; ++i)
#define int long long
using namespace std;

constexpr int N = (1<<12)+10, M = 20;

int len, cnt[N], w[M], dp[N][110];
void init() {
    rep(s1,1<<len) if (cnt[s1]) rep(s2,1<<len) {
        int ret = 0;
        rep(b,len) {
            int b1 = s1&(1<<b), b2 = s2&(1<<b);
            if (b1 == b2) ret += w[len-b];
        }
        if (ret <= 100) dp[s2][ret] += cnt[s1];
    }
    rep(s,1<<len) For(j,100) dp[s][j] += dp[s][j-1];
}

int get(const string &s) {
    int ret = 0;
    rep(j,len) if (s[j] == '1') ret += 1<<(len-1-j);
    return ret;
}

int n, q;
signed main() {
    fast;
    cin >> len >> n >> q;
    For(i,len) cin >> w[i];
    For(i,n) { string s; cin >> s; ++cnt[get(s)]; }
    init();
    while (q-- > 0) {
        string s; cin >> s;
        int k; cin >> k;
        cout << dp[get(s)][k] << '\n';
    }
    return 0;
}