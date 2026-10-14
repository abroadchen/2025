//
// Created by Psy.C on 2026/10/14.
//
/**
比较器 s*o.h > h*o.s 即 s/h > o.s/o.h，按 s 占比从高到低排序（含 h 越多的越排后面）。这是贪心核心：s 多的先放，让累计 s 尽快变大
遍历每个字符串，统计其中 s、h 的个数。
ans += e[i].s：在串内，每读到第 j 个字符为 h 时，这个串里它前面已有 e[i].s 个 s，于是新增 e[i].s 个 "sh" 子序列——这统计的是单个字符串内部的贡献
cnt = 处理完前 i-1 个串后累计的 s 总数。
当前串有 e[i].h 个 h，每个都可与前面 cnt 个 s 配对，新增 cnt * e[i].h。
然后累加当前串的 s 数到 cnt
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;
struct node {
    ll s, h;
    bool operator<(const node &o) const {
        return s*o.h > h*o.s;
    }
} e[N];

ll n, ans, cnt;
string s;
int main() {
    fast;
    cin >> n;
    for (ll i = 1; i <= n; ++i) {
        cin >> s;
        for (ll j = 0; j < s.length(); ++j) {
            if (s[j] == 's') e[i].s++;
            if (s[j] == 'h') e[i].h++, ans += e[i].s;
        }
    }
    sort(e+1, e+1+n);
    for (ll i = 1; i <= n; ++i) {
        ans += cnt*e[i].h;//该串所有 h 与前面累计的 cnt 个 s 配对
        cnt += e[i].s;//更新累计 s 数
    }
    cout << ans;
    return 0;
}