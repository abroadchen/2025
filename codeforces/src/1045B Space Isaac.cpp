//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
NA 是 哈希基数（大质数/随机值，作用类似字符串哈希里的 base）。
pre[] 正向哈希前缀、nxt[] 反向哈希后缀、fac[] 基数幂 HA^i。
用 unsigned long long，让哈希乘积自然溢出取模 2^64，这是常见的"无模哈希"技巧
这是一条区间相等判断：判断下标区间 [l, r] 上的「正向哈希」与「反向哈希」是否相等，等价于判断这段子序列是否回文（正着读=倒着读）。

pre[r] - pre[l-1]*fac[r-l+1]：子串 [l,r] 的正向哈希。
nxt[l] - nxt[r+1]*fac[r-l+1]：子串 [l,r] 的反向哈希（倒序时的哈希）。
两者相等 ⇔ 区间 [l,r] 的差分序列是回文。
这利用了多项式滚动哈希的性质：hash(l,r) = pre[r] - pre[l-1]*base^(r-l+1)
fac[i] = HA^i。
pre[i] 是 b[1..i] 的哈希，多项式和形式。
nxt[i] 从 b[i] 到 b[n-1] 的哈希（逆向累加），注意边界 nxt[n]=0。
把原数组 a 转成相邻差 b[i] = a[i+1]-a[i]，长度是 n-1。
哈希正是在差分数组 b 上做的（b 下标 1..n-1）
解读：这是在测试每个位置 i 能否作为「环的某个对称拼接点」，本质是判断数组 a 能否构成某个"环形等差"结构。

check(1, i-1)：断开点左边这段差分是否回文。
check(i+1, n-1)：断开点右边这段差分是否回文。
a[1]+a[i] == a[i+1]+a[n]-m：一个跨界的算术关系守恒条件（环上的首尾相接充当等差桥）。
三项同时成立，就把 (a[1]+a[i]) % m 记作一个合法解，并收集到 ans[]
输出解的数量 cnt。
将所有解 ans 排序后逐个输出（升序）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
#define ull unsigned long long
using namespace std;

constexpr int N = 2e5+5;
constexpr ull HA = 41793404541;

ull pre[N], fac[N], nxt[N];
bool check(int l, int r) {
    return pre[r] - pre[l-1]*fac[r-l+1] == nxt[l] - nxt[r+1]*fac[r-l+1];
}

int n, m, a[N], b[N], ans[N], cnt;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n-1) b[i] = a[i+1] - a[i];
    fac[0] = 1;
    rep(i,n) fac[i] = fac[i-1]*HA;
    rep(i,n) pre[i] = pre[i-1]*HA + (ull)b[i];
    for (int i = n-1; i; --i) nxt[i] = nxt[i+1]*HA + (ull)b[i];
    rep(i,n) {
        bool f = 1;
        if (i != 1) f &= check(1, i-1);
        if (i != n) {
            f &= a[1] + a[i] == a[i+1] + a[n] - m;
            if (i != n-1) f &= check(i+1, n-1);
        }
        if (f) ans[++cnt] = (a[1] + a[i]) % m;
    }
    cout << cnt << '\n';
    sort(ans+1, ans+cnt+1);
    rep(i,cnt) cout << ans[i] << ' ';
    return 0;
}