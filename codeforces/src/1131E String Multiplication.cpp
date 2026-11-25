//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
p[i] 存第 i 个字符串；res 存最终答案
对 26 个字母分别跑一遍，ans 记录用字符 c 能拼出的最长的连续段
遍历一遍同时算 4 个量：

f：整串是否全由 c 组成。
mx：串内 c 的最大连续段长（用于拼接/非拼接参考）。
l：前缀连续 c 的个数（从开头数）。
r：后缀连续 c 的个数（从末尾数，通过 reverse 后数前缀实现）
情况 1（f==1，整串全是 c）
这个“全 c”串接到现有连续段后面会延续，形成 ans 个 c + 本串的 mx 个 c。
但因这个串全 c，它可以整体叠在中间，使连续段暴增。代码用 (ans+1)*mx（每个前段字符 +1，串内每个 c 都延长），是经典递推式
情况 2（f==0 但已有 ans 拼接）
当前串不全 c，它不能整个续接，只能：
取它自己的内部最长段 mx；或
接在已拼段后面：前段末尾若全是 c（有 ans 个）→ 本串前缀 l + 后缀 r 能与前后相连 → l + r + 1（前段末 1 个 + 前缀 + 后缀），取 max。
情况 3（f==0 且还没拼接）
第一个非全 c 串，只能取自身内部最长段
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e5+5;
int n, res;
string p[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> p[i];
    for (char c = 'a'; c <= 'z'; c++) {
        int ans = 0;
        rep(i,n) {
            bool f = 1;
            for (char s : p[i]) if (c != s) { f = 0; break; }
            int mx = 0, cur = 0, l = 0, r = 0;
            for (char s : p[i]) {
                if (s == c) ++cur; else cur = 0;
                mx = max(mx, cur);
            }
            for (char s : p[i]) { if (s == c) ++l; else break; }
            ranges::reverse(p[i]);
            for (char s : p[i]) { if (s == c) ++r; else break; }
            if (f) ans += (ans+1)*mx;
            else if (ans) ans = max(mx, l+r+1);
            else ans = mx;
        }
        res = max(res, ans);
    }
    cout << res;
    return 0;
}