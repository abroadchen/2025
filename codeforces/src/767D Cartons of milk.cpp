//
// Created by Psy.C on 2026/9/7.
//
/**
n：第一组元素个数，m：第二组元素个数（推测），k：某个上限参数。
cnt[x]：对数值 x 计数（第一组里值为 x 的个数）→ 后变为前缀和。
mx：出现的最大数值。
v：存 (数值, 编号) 的向量。
ans：最终回答的编号集合

读入 n 个数，对每个值 x 做 cnt[x]++（计数），更新 mx。
读入 m 个数，每个以 (x, i) 形式存入 v，i 是它在第二组里的编号。
按数值（first）升序排序 v
第一步变成前缀和：现在 cnt[i] = "第一组中数值 ≤ i 的元素个数"。
第二步：cnt[i] = (i+1)*k - cnt[i]。
(i+1)*k 是"到第 i 个数值档位上，理论可容纳/需要的某种总量"。
减去前缀和后，cnt[i] 变成差值/余额——即"当前档位相对某个目标还差多少（或富余多少）"。负值表示不够

mn 从 inf 开始，now 指向 v 排序后的最后一个（数值最大者）。
从 i = mx 递减到 0：
mn = min(mn, cnt[i])：mn 是在扫描过程中看到的所有 cnt[i] 的最小值（从高往低的"历史最小值"）。
if (mn < 0) return puts("-1")：一旦历史最小余额变负，说明约束无法满足，输出 -1 终止。
内层 while：把 now 往前挪到数值 ≤ i 的最大元素。
若还有且 mn > 0：把所有数值恰为 i 的元素 v[now]（从大到小）依次选中，压入 ans，同时 mn--（每选一个就消耗一单位的"余量 mn"
将选中的编号排序（因为是按数值从大到小入栈的，编号是无序的）。
先输出选中数量，再输出所有编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e7+5, inf = 1e14;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k, cnt[N], mx=0;
vector<ii> v;
vector<int> ans;
signed main() {
    fast;
    n = rd(), m = rd(), k = rd();
    for (int i = 1, x; i <= n; ++i)
        x = rd(), cnt[x]++, mx = max(mx, x);
    for (int i = 1, x; i <= m; ++i)
        x = rd(), v.emplace_back(x, i), mx = max(mx, x);
    ranges::sort(v);
    for (int i = 1; i <= mx; ++i) cnt[i] += cnt[i-1];
    for (int i = 0; i <= mx; ++i) cnt[i] = (i+1)*k-cnt[i];
    int mn = inf, now = v.size()-1;
    for (int i = mx; i >= 0; --i) {
        mn = min(mn, cnt[i]);
        if (mn < 0) return puts("-1");
        while (now >= 0 && v[now].first > i) now--;
        if (now == -1) continue;
        while (now >= 0 && mn > 0 && v[now].first == i)
            ans.push_back(v[now].second), --now, --mn;
    }
    ranges::sort(ans);
    cout << ans.size() << '\n';
    for (auto i : ans) cout << i << ' ';
    return 0;
}