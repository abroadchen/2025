//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
求模式串 t 每个前缀的最长 border（最长相同前后缀）长度，存入 fail[i]
注 1：if (j < i) ++cnt[j]; else ++cnt[fail[j]]; 中，j 与 i 在绝大多数情况下 j < i 恒成立，所以实际几乎总是执行 ++cnt[j]。也就是说它统计的是：每次匹配到长度为 j 的前缀时，cnt[j] 自增，即记录"文本扫描过程中，模式串每个前缀 j 被匹配到的次数"。j==i 的 else 分支几乎不会触发。

注 2：这里其实存在语义歧义/潜在 bug——它没有在 j == m（完整匹配）时专门累加答案，而是把"完整匹配"也当作普通前缀计入 cnt，靠后续的 fail 树汇聚与循环节扣减来体现答案。这正是这份代码的特殊设计（配合 (ans=n)*=m 的使用方式）
把每个位置计数累加到其 fail 前缀上——得到 cnt[i] = 以 t 前 i 个字符为 border/后缀的匹配次数之和。这是标准的 fail 树贡献汇聚
初始化答案 = n × m
遍历每个位置 i，若 fail[i] 非零（有 border），i - fail[i] 是 [1..i] 的最小循环节长度。
用 cnt[i-fail[i]]（该循环节对应的出现次数）从 ans 中扣减，实现"重复循环构成的子串只计一次"的效果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

char s[N], t[N];
int fail[N], cnt[N];
ll ans;
int main() {
    fast;
    scanf("%s", s+1); scanf("%s", t+1);
    int n = strlen(s+1), m = strlen(t+1);
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && t[j+1] != t[i]) j = fail[j];
        j += t[j+1] == t[i];
        fail[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && t[j+1] != s[i]) j = fail[j];
        j += t[j+1] == s[i];
        if (j < i) ++cnt[j]; else ++cnt[fail[j]];
    }
    for (int i = m; i; --i) cnt[fail[i]] += cnt[i];
    (ans = n) *= m;
    for (int i = 1; i <= m; ++i)
        if (fail[i] && i - fail[i] > 0) ans -= cnt[i-fail[i]];
    cout << ans << '\n';
    return 0;
}