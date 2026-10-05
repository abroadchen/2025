//
// Created by Psy.C on 2026/10/5.
//
/**
M=15：最多处理的子串长度上限。
pre / suf：字符串的前缀/后缀（用于拼接）。
flg：标记字符串是否已"超长"（长于 M，或被拼接成超长）。
mk：bitset<N>。N=65536=2^16，用于标记所有长度为 1..15 的二进制子串是否出现过。mk[i|(1<<(len))] 表示"长度为 len 的、值为 i 的子串"是否出现过（用最高一位存长度信息）。
rt：答案，即该字符串的最小缺失子串长度。
关键设计：把字符串视为二进制序列（s[i]&1 取最低位），枚举长度 1..M 的所有连续子串，计算其二进制值 t，用 mk[t | (1<<len)] 标记。这样可高效查询"某长度下有哪些值出现"
拼接两个字符串 a、b：

前缀：若 a 未超长，前缀 = a.pre + b.pre，若超过 M 则截断到 M 并置 flg=true；若 a 已超长，前缀就用 a.pre。
后缀：类似，取 a.suf + b.suf，超长保留后 M 个字符。
标记新子串：s = a.suf + b.pre——只有拼接交界处可能产生新子串（长度 M 内），枚举 s 的所有长度 ≤M 的连续子串，更新 mk。
计算 rt：从长度 1 开始找，第一个"某长度下有值 i 未出现"的长度即为答案
对长度 len=rt.rt+1：遍历所有 i ∈ [0, 2^len)，检查 mk[i | (1<<len)] 是否都为 1（即该长度所有二进制子串都出现过）。一旦找到某个 i 没出现过，则该长度就是最小缺失子串长度，rt.rt = len-1（因为循环先 ++rt.rt）。

实际语义：rt 输出的是能整除的最小长度？看输出 cout << ss[n+i].rt。结合后面 solve，rt 是最小无法全部覆盖的长度
读入 n 个初始字符串，对每个字符串：

suf = pre。
mk[1] = 1：标记长度 0（空串）——1 = 0 | (1<<0)，即长度为 0 的"空子串"出现过，这是为了后续判定。
枚举从位置 j 开始的长度 1..M 的子串，标记到 mk
读入 m 次操作，每次 ss[a] + ss[b] 拼出一个新串存入 ss[n+i]，并输出其 rt
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 65536, M = 15, K = 205;
struct str {
    string pre, suf;
    bool flg;
    int rt{};
    bitset<N> mk;
    str():flg(false){}
} Str;

str operator+(str& a, str& b) {
    str rt;
    rt.flg = a.flg || b.flg; rt.mk = a.mk|b.mk;
    if (!a.flg) {
        rt.pre = a.pre + b.pre;
        if (rt.pre.length() > M)
            rt.flg = true, rt.pre.resize(M);
    } else rt.pre = a.pre;
    if (!b.flg) {
        rt.suf = a.suf + b.suf;
        if (rt.suf.length() > M)
            rt.flg = true, rt.suf = rt.suf.substr(rt.suf.size()-M, rt.suf.size());
    } else rt.suf = b.suf;
    string s = a.suf + b.pre;
    for (int i = 0; i < s.length(); ++i) {
        for (int j = 0, t = 0; j < M && i+j < s.length(); ++j) {
            t = (t<<1)|(s[i+j]&1);
            rt.mk[t|(1<<(j+1))] = 1;
        }
    }
    int i;
    for (rt.rt = 0; ; ++rt.rt) {
        for (i = 0; i < (1<<(rt.rt+1)) && rt.mk[i|(1<<(rt.rt+1))]; ++i) {}
        if (!rt.mk[i|(1<<(rt.rt+1))]) break;
    }
    return rt;
}

int n;
str ss[K];
inline void init() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> ss[i].pre;
        ss[i].suf = ss[i].pre; ss[i].mk[1] = 1;
        for (int j = 0; j < ss[i].pre.length(); ++j)
            for (int k = 0, t = 0; k < M && j+k < ss[i].pre.length(); ++k) {
                t = (t<<1)|(ss[i].pre[j+k]&1);
                ss[i].mk[t|(1<<(k+1))] = 1;
            }
    }
}

int m;
inline void solve() {
    cin >> m;
    for (int i = 1, a, b; i <= m; ++i) {
        cin >> a >> b;
        ss[n+i] = ss[a] + ss[b];
        cout << ss[n+i].rt << '\n';
    }
}


int main() {
    fast;
    init(); solve();
    return 0;
}