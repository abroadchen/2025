//
// Created by Psy.C on 2026/9/23.
//
/**
f[num(ch)]：统计 t 中每个字符出现几次（作为"每构造出 1 份完整 t 所需的各字符配额"）。
c：动态计算的"剩余可分配额度"。
k：s 中 ? 的数量（即可用于补字符的总自由额度）
若要做 x 份 t，需要每种字符 f*×x 个。
先让 s 里已固定的非 ? 字符去抵扣对应配额（每个字符可用一次）。
剩下的配额总和 cnt 就是还需要用 ? 补齐的字符数；若 cnt <= k（? 够用）则可构造 x 份，否则不行。
单调性保证可二分：x 越大所需字符越多，越难满足
二分搜索"最多能凑出几个完整 t"，左界 0，右界设为大值 1e6
重新用 l（最优次数）算配额。
固定字符抵完后，遍历每个 ?：优先把配额不足的字符补齐（按序找仍 c[j]>0 的字符填一个），若所有配额已满则填 'a'
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e6+5, M = 26;
int num(char x) { return x - 'a'; }

ll c[M], f[M];
char s[N];
int n, k;
bool check(int x) {
    ll cnt = 0;
    for (int i = 0; i < M; ++i) c[i] = f[i]*x;
    for (int i = 1; i <= n; ++i)
        if (s[i] != '?' && c[num(s[i])])
            --c[num(s[i])];
    for (ll& i : c) cnt += i, i = 0;
    if (cnt > k) return 0;
    return 1;
}

char t[N];
int m, l, r = N;
int main() {
    scanf("%s%s", s+1, t+1);
    n = strlen(s+1); m = strlen(t+1);
    for (int i = 1; i <= n; ++i)
        if (s[i] == '?') ++k;
    for (int i = 1; i <= m; ++i) ++f[num(t[i])];
    while (l + 1 < r) {
        int mid = (l+r)/2;
        if (check(mid)) l = mid; else r = mid;
    }
    for (int i = 0; i < M; ++i) c[i] = f[i]*l;
    for (int i = 1; i <= n; ++i)
        if (s[i] != '?' && c[num(s[i])]) --c[num(s[i])];//固定字符抵配额
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '?') {
            bool ok = 1;
            for (int j = 0; j < M; ++j) {
                if (c[j]) {
                    printf("%c", j+'a');
                    --c[j];
                    ok = 0;
                    break;
                }
            }
            if (ok) printf("a");//配额全部满足后剩余 '?' 随便填 'a'
        } else printf("%c", s[i]);
    }
    return 0;
}