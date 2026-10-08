//
// Created by Psy.C on 2026/10/8.
//
/**
从右往左扫，用单调递增栈维护"右边尚未被更小元素替代"的位置。
弹出栈顶所有 >= a[i] 的元素，剩下的栈顶就是
i
i 右边第一个严格小于
a
[
i
]
a[i] 的下标，存进 p[i]。
st[0]=n+1 作为哨兵，表示"右边没有更小元素"时 p[i]=n+1
扫描每个位置
i
i，若其右边最近更小元素下标 p[i] 与
i
i 的距离超过 k（即这个下降不能在一步内处理），标记为"有问题"的位置。
mn/mx 记录这些问题位置的最小/最大下标，cur 记录这些问题位置中 a[i] 的最小值
若没有"坏"下降对，直接 YES。
pos = mn + k：从最左问题位置出发能覆盖到的位置。若这个 pos 已越过最右问题位置 mx，说明区间冲突无法同时处理 → NO
从右往左找"比 cur 小且尽可能大"的元素作为可交换/可替换的候选 ans；若找不到（ans<0）→ NO
若从 pos 起的窗口范围能覆盖到末尾 → YES。
否则检查窗口 [pos+1, pos+k] 内是否存在比 ans 小的元素，有则 YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5, inf = 0x3f3f3f3f;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], st[N], tp, p[N];
int main() {
    fast;
    int n = rd(), k = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    st[0] = n+1;
    for (int i = n; i; --i) {
        while (tp && a[st[tp]] >= a[i]) --tp;
        p[i] = st[tp];
        st[++tp] = i;
    }
    int cur = inf, mn = 0, mx = 0;
    for (int i = 1; i <= n; ++i)
        if (p[i] - i > k) {
            if (!mn) mn = i;
            mx = i;
            cur = min(cur, a[i]);
        }
    if (cur == inf) { cout << "YES\n"; return 0; }
    int pos = mn + k;
    if (pos <= mx) { cout << "NO\n"; return 0; }
    int ans = -inf;
    for (int i = n; i; --i)
        if (a[i] < cur && a[i] > ans) ans = a[i];
    if (ans < 0) { cout << "NO\n"; return 0; }
    if (pos + k > n) { cout << "YES\n"; return 0; }
    for (int i = pos+1; i <= pos+k; ++i)
        if (a[i] < ans) { cout << "YES\n"; return 0; }
    cout << "NO\n";
    return 0;
}