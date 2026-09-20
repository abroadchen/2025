//
// Created by Psy.C on 2026/9/20.
//
/**
把模式串 t 倒着和 s 中对应段比较（s[p-j+1] 与 t[m-j+1]）。
若 s 对应的字符既不等于 t 对应字符、也不是 ?，则失配 → false。
注意：这里只允许 s 的位置是 ? 时通配；t 本身不含 ?（模式串是具体字符）。如果 s 该位置是普通字符，则必须等于 t 对应字符。
语义：check(p) = "模式 t 是否能匹配 s 中 [p-m+1, p] 这段"，匹配规则是 s 的 ? 可当任意字符
对模式串 t 求 KMP 的 next 数组（失配函数），nxt[i] = t[1..i] 的最长相等前后缀长度。
用途：当两个"已匹配的模式实例"在 s 中重叠时，重叠长度必须是一个 border（前后缀相等），才能同时成立——用 nxt 链枚举可重叠匹配的转移
f[i] = s 的前缀 s[1..i] 中最多能匹配出多少个模式 t（不要求都连续）。
f[i] = f[i-1]：不把 i 作为匹配结尾，继承前面。
若 check(i) 为真（模式可在 i 处结束匹配）：
g[i] = f[i-m] + 1：若是不相重叠的新匹配（占 [i-m+1, i]），则前面最多 f[i-m] 次 + 本次 1 次。
枚举可重叠：for (j = nxt[m]; j; j = nxt[j])
j 是模式 t 的一个 border 长度（suffix of t = prefix of t）。
g[i-(m-j)] + 1：如果前面某个匹配的结尾在 i-(m-j)，且两个匹配共享长为 j 的重叠（前缀/后缀相等），则可以在不冲突下再叠加一次。
取这些可重叠方案的最大值。
f[i] = max(f[i], g[i])：更新 f[i]。
为什么用 border（nxt 链）： 两个模式实例重叠时，重叠部分必须既是前面的 suffix 又是后面的 prefix——这正是 border 的定义，所以只能从 nxt[m] 沿失配链转移。
输出 s 中最多能匹配出的模式 t 的次数（允许重叠，重叠需满足 border）
 */

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10;

int m;
char s[N], t[N];
bool check(int p) {
    for (int j = 1; j <= m; ++j)
        if (s[p-j+1] != t[m-j+1] && s[p-j+1] != '?')
            return false;
    return true;
}

int n, nxt[N], f[N], g[N];
int main() {
    fast;
    scanf("%s%s", s+1, t+1);
    n = strlen(s+1); m = strlen(t+1);
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && t[j+1] != t[i]) j = nxt[j];
        if (t[j+1] == t[i]) j++;
        nxt[i] = j;
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i-1];
        if (check(i)) {
            g[i] = f[i-m] + 1;
            for (int j = nxt[m]; j; j = nxt[j])
                g[i] = max(g[i], g[i-(m-j)]+1);
            f[i] = max(f[i], g[i]);
        }
    }
    cout << f[n] << '\n';
    return 0;
}