//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
cin >> n：网格规模（有 n 行，每行字符串解析后得到 n 位）。
每行读入字符串 s，rep(i,n) 从 1 开始。
int top = 0：当前行内已填的列号计数。
对字符串每个字符 s[j]：
若是 '0'-'9' → x = 字符 - '0'（0-9）。
否则是字母（本题是 'A' 起）→ x = 字符 - 'A' + 10（10-15）。
这是把单个十六进制字符转成 0-15 的整数。
内层 for k = 3; k >= 0; k--：把 x（0-15，4 位二进制）从高位到低位拆出每一位。
(x>>k) & 1 取出第 k 位（3,2,1,0 依次是最高位到最低位）。
top++，并存进 a[i][top]。
因为每个十六进制字符是 4 个二进制位，若每行共有 (s.length()*4) 位。题目约定恰好组成 n 列（即 4 * len == n）。
结果：a[1..n][1..n] 是一张 01 矩形网格，行下标 1..n，列下标 1..n。
ans 初始为 n（答案 gcd 初始设定为 n，作为合理上界/初值，因为结果不可能超过 n）。
对每一行 i：
cnt：当前连续相同值的长度。
g = n：这一行的游程长度集合的 gcd，初值 n（中性，方便与第一个游程求 gcd）。
rep(j,n) 遍历该行的每一列：
cnt++。
若越界（j == n）或者当前值 a[i][j] 与右边 a[i][j+1] 不同 → 说明一个连续段结束了，把这个段的长度 cnt 与 g 做 gcd，再重置 cnt=0。
处理完整行后，ans = gcd(ans, g)：把这一行的游程 gcd 并入全局答案。
目的：找出每一行里"相同值连续段长度"的公约数，GCD 后再对所有行取 gcd
与行版本对称，遍历每一列 j：
对每一行 i，cnt++；若 i==n 或 a[i][j] 与下一行 a[i+1][j] 不同，则结束一个列段，把 cnt 与 g 取 gcd，重置。
一列处理完，ans = gcd(ans, g)。
同样存在 a[i+1][j]（读第 n+1 行）的越界访问，靠 i==n 短路保护
输出最终 gcd —— 各行列连续段长度的最大公约数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 6111;
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int n, a[N][N];
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        string s; cin >> s;
        int top = 0;
        for (int j = 0; j < s.length(); j++) {
            int x = 0;
            if (s[j] >= '0' && s[j] <= '9') x = s[j] - '0';
            else x = s[j] - 'A' + 10;
            for (int k = 3; k >= 0; k--) { top++; a[i][top] = (x>>k)&1; }
        }
    }
    int ans = n;
    rep(i,n) {
        int cnt = 0, g = n;
        rep(j,n) {
            cnt++;
            if (j == n || a[i][j] != a[i][j+1]) { g = gcd(g, cnt); cnt = 0; }
        }
        ans = gcd(ans, g);
    }
    rep(j,n) {
        int cnt = 0, g = n;
        rep(i,n) {
            cnt++;
            if (i == n || a[i][j] != a[i+1][j]) { g = gcd(g, cnt); cnt = 0; }
        }
        ans = gcd(ans, g);
    }
    cout << ans;
    return 0;
}