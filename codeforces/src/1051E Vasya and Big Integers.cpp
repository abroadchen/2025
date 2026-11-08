//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
a = " " + a：在开头加占位符，让下标从 1 开始。
z[i]：以 i 开头的子串与整个串的最长公共前缀（LCP）长度。
l, r：维护已探测到的"Z-box"区间 [l, r]，利用之前结果加速。
初始化：z[i] = i <= r ? min(z[i-l+1], r-i+1) : 0;（复用 Z-box 内的已知值）；while 扩展比较；最后更新 Z-box。
这是标准的线性 Z 函数，时间复杂度 O(n)
返回数组 p，其中 p[i] = a 中以位置 i 开头的子串 与 b 的 LCP 长度（即从 a 的 i 位置能匹配上 b 的前多少个字符）。
结构和 Z 算法一样，只是比较对象是 a 的子串与 b。这里对 b 预求 Z，再用滑动窗口（Z-box）复用。
这样得到 p[i] 后，就能快速判断 "a 的某一段是否大于/小于 l 或 r"。
相当于：没写标准 KMP 的匹配函数，而是用 Z 算法实现了"每个位置 vs 模式串 b 的 LCP"。函数名取 kmp，实为"逐位置前缀匹配"
nl, nr：l、r 的长度；
vl = Str::kmp(a, l)：位置 i 处 a 子串与 l 的 LCP；
vr = Str::kmp(a, r)：位置 i 处 a 子串与 r 的 LCP。
调用 ckl(i) 表示：段落 a[i-nl+1 .. i]（以 i 结尾、长度 nl 的一段）作为候选整数，判断其值是否 ≥ l。
j = i - nl：段起点前一位；pos = vl[j+1] 是"起点在 j+1"的 a 子串与 l 的 LCP。
若段首是 '0' 且 nl>1 → 有前导零，非法，返回 0。
拼接比较：pos >= nl 说明整段与 l 完全相同 → 相等 → ≥ l 成立；否则看第一个不同字符 a[j+pos+1] > l[pos+1] → 大于 → 成立；否则不成立。
用长度 nl 段自然与 l（长度 nl）比较。用 len=nl 的分段式处理
判断以 i 结尾、长度 nr 的一段 ≤ r：前导零拒绝；若与 r 完全相等（pos>=nr）或第一个不同字符 < r[pos+1] 则成立。
逻辑与 ckl 对称。

读入被拆分串 a、下界 l、上界 r。
预计算 vl（a 各位置与 l 的 LCP）、vr（a 各位置与 r 的 LCP）。
三个串前加空格占位，使下标从 1 开始
dp[0]=1：空前缀有 1 种拆分（空拆分）；
s[i]：前缀 dp[0..i] 的累加和（用于批量转移）；
s0[i]：对"以某种特殊方式贡献"的 dp 的累加和
这里分两大分支：nl == nr（上下界长度相同）‍ 和 nl != nr（长度不同）‍。

分支 A：nl == nr
此时每段长度固定为 nl == nr，没有别的长度可选。
如果以 i 结尾、长度 nl 的那一段同时满足 ≥l 且 ≤r（ckl && ckr——这两处比较长度相同，比较自然的数字值），则方案数加上 dp[i-nl]。
即：最后一段固定长度，继承前 i-nl 前缀的方案数。
分支 B：nl != nr（长度不同）

这里一个"段"可能是长度 nl，也可能是长度 nr，还可能是介于两者之间的任意长度（因为整数值比较时，更长的数字一定更大）。代码用三个来源相加
长度为 nl 的段：只要 ≥ l 即可（长度固定 nl，比 l 长会产生前导零被 ckl 拒绝；长度相等比较值）。
长度为 nr 的段：只要 ≤ r 即可。
注意分支 B 里左右端比较不要求同时相等，因为长度不同，只要各自的上下界条件满足即可
这里处理中间长度（nl < 段长 < nr，或相反）的段：这类长度的数字串天然满足 l ≤ 段 ≤ r（因为长度介于两者之间，数值必然在区间内部，无需逐位比较），但要排除"前导零"等边界。
用前缀和 s、s0 一次性累加区间内所有可行尾长，避免 O(长度) 枚举。
具体区间划分为 [i-nr, i-nl-1] 之类，s0 用于剔除那些带前导零的非法起点。
条件判断保证下标不越界，且正确限定"中间段"的长度范围（比 nl 长、比 nr 短的部分）。
这部分的区间逻辑是整题最精细的地方，等价于：对 "段长 X ∈ (nl, nr)" 的所有 X，dp[i] += dp[i-X]，用前缀和 O(1) 完成，同时用 s0 处理首字符 '0' 的排除规则
s0[i]：特殊累加——当 a[i+1]=='0'（即当前位置下一字符是 0，意味着该位置作为段尾会导致段首... 实际是处理"以 i 结尾、但下一个字符为 0 时该 dp 值是否能作为无前导零段的来源"的标记），将 dp[i] 计入 s0。
dp[i] = (dp[i]%mod+mod)%mod：把可能为负的差分结果转正。
s[i] = (s[i-1] + dp[i])%mod：普通前缀和。
s0 的作用：在中间段区间累加时，剔除那些"当作段尾后下一字符是 0、会导致前导零非法"的起点，保证每段的首字符不为 0（除非段长为 1）
输出把整个串 a（长度 n）拆分的合法方案数，对 mod 取模后结果


Z(b)	Z 函数：b 各后缀与 b 的 LCP
kmp(a,b)	返回 p[i] = a 位置 i 开头子串 与 b 的 LCP
vl[i]	a 位置 i 与 l 的 LCP
vr[i]	a 位置 i 与 r 的 LCP
ckl(i)	以 i 结尾、长度 nl 的段 ≥ l 且无前导零？
ckr(i)	以 i 结尾、长度 nr 的段 ≤ r 且无前导零？
dp[i]	前缀 a[1..i] 的合法拆分方案数
s[i]	dp 前缀和（归一化）
s0[i]	dp 前缀和（仅限"段首非0"的合法来源）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define ll long long
using namespace std;

constexpr int N = 1e6+10, mod = 998244353;

namespace Str {
    vi Z(string a) {
        int n = a.size();
        vi z(n+1, 0); a = " " + a;
        int l = 0, r = 0;
        for (int i = 2; i <= n; i++) {
            z[i] = i <= r ? min(z[i-l+1], r-i+1) : 0;
            while (i+z[i] <= n && a[1+z[i]] == a[i+z[i]]) ++z[i];
            if (i+z[i]-1 > r) r = i+z[i]-1, l = i;
        }
        return z;
    }
    vi kmp(string a, string b) {
        vi z = Z(b);
        int n = a.size(), m = b.size();
        vi p(n+1, 0); a = " " + a, b = " " + b;
        int l = 0, r = 0;
        for (int i = 1; i <= n; i++) {
            p[i] = i <= r ? min(r-i+1, z[i-l+1]) : 0;
            while (i+p[i] <= n && b[1+p[i]] == a[i+p[i]]) p[i]++;
            if (i+p[i]-1 > r) r = i+p[i]-1, l = i;
        }
        return p;
    }
}

int nl, nr;
vi vl, vr;
string a, l, r;
inline bool ckl(int i) {
    int j = i - nl, pos = vl[j+1];
    if (a[j+1] == '0' && nl > 1) return 0;
    if (pos >= nl || a[j+pos+1] > l[pos+1]) return 1;
    return 0;
}
inline bool ckr(int i) {
    int j = i - nr, pos = vr[j+1];
    if (a[j+1] == '0' && nr > 1) return 0;
    if (pos >= nr || a[j+pos+1] < r[pos+1]) return 1;
    return 0;
}

int n;
ll dp[N], s[N], s0[N];
void solve() {
    cin >> a >> l >> r; n = a.size(); nl = l.size(), nr = r.size();
    vl = Str::kmp(a, l), vr = Str::kmp(a, r);
    a = " " + a, l = " " + l, r = " " + r;
    dp[0] = s[0] = 1; s0[0] = a[1] == '0';
    for (int i = 1; i <= n; i++) {
        if (nl == nr) {
            if (i >= nl) if (ckl(i) && ckr(i))
                dp[i] = (dp[i] + dp[i-nl])%mod;
        } else {
            if (i >= nl) if (ckl(i)) dp[i] = (dp[i] + dp[i-nl])%mod;
            if (i >= nr) if (ckr(i)) dp[i] = (dp[i] + dp[i-nr])%mod;
            if (i-nl-1 >= 0 && i-nr >= 0 && i-nl-1 >= i-nr) {
                dp[i] = (dp[i] + s[i-nl-1] - s0[i-nl-1]) % mod;
                dp[i] = (dp[i] + s0[i-nr] - s[i-nr]) % mod;
            }
            else if (i-nl-1 >= 0 && i-nr <= 0) dp[i] = (dp[i] + s[i-nl-1] - s0[i-nl-1]) % mod;
        }
        s0[i] = (s0[i] + s0[i-1]) % mod;
        dp[i] = (dp[i]%mod + mod)%mod;
        if (a[i+1] == '0') s0[i] = (s0[i] + dp[i]) % mod;
        s[i] = (s[i-1] + dp[i]) % mod;
    }
    cout << dp[n];
}


int main() {
    fast;
    solve();
    return 0;
}