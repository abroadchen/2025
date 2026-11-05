//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
n：段数
h：某个"高度/长度"参数（决定了可额外跨越的最大量）
l[i], r[i]：第 i 段的左、右边界（区间 [l[i], r[i]]）
s[i]：前缀和数组（累计间隔）
mx：答案最大值
读入 n、h。
对每段读入 l[i], r[i]。
计算 s[i] = s[i-1] + (l[i] - r[i-1])：
r[i-1] 是前一段的右端点，l[i] 是当前段的左端点。
l[i] - r[i-1] = 两段之间的间隔（缺口）长度。
所以 s[i] 是从第 1 段开始，到第 i 段为止所有段间间隔的累计和（s[1] 本身是 l[1]-r[0]，其中 r[0]=0）
对每个左端点 i，尝试找到能覆盖的最远右端点 j。

第一步：二分找 j
在前缀和 s[1..n] 中，二分查找第一个 ≥ h+s[i] 的位置，再减 1 得到 j。
含义：找到最靠右的段 j，使得 s[j] < h + s[i]，即 s[j] - s[i] < h。
由于 s[j]-s[i] 表示第 i+1..j 段的累计间隔和，这个条件等价于：从第 i 段到第 j 段之间的所有缺口累计长度小于 h。
也就是说：在"总可用缺口预算 h"的约束下，以 i 为左端，最远能覆盖到第 j 段
第二步：计算该覆盖的"答案"
r[j] - l[i]：从第 i 段左端到第 j 段右端的总跨度。
s[j] - s[i]：这段跨度里真正"缺口的累计长度"。
h - (s[j]-s[i])：用掉缺口后剩余可用的预算。
剩余预算就是还能额外向左右延伸的量——这里 +(h - s[j] + s[i])（即剩余预算）被加到跨度上。
即：实际可覆盖长度 = 跨度 + 剩余缺口预算。意思是剩下的 h 预算还能再多覆盖一点距离。
合起来：ans = (覆盖跨度) + (预算余量)，表示以 i 为起点、在 h 预算内可得到的最大连续覆盖长度。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e6+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, h, l[N], r[N], s[N], mx;
signed main() {
    fast;
    n = rd(), h = rd();
    rep(i,n) {
        l[i] = rd(), r[i] = rd();
        s[i] = s[i-1] + (l[i] - r[i-1]);
    }
    rep(i,n) {
        int j = lower_bound(s+1,s+1+n,h+s[i]) - s - 1;
        int ans = r[j] - l[i] + (h - s[j] + s[i]);
        mx = max(mx, ans);
    }
    cout << mx;
    return 0;
}