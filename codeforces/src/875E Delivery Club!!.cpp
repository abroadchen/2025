//
// Created by Psy.C on 2026/10/6.
//
/**
qmx(l,r)：O(1) 返回区间 [l,r] 的最大值。
qmn(l,r)：O(1) 返回区间 [l,r] 的最小值。
都是标准 Sparse Table 查询（用 __lg 取 floor(log2(len))，两段取并）
p 初值 n+1，表示当前段的"结尾+1"（即本段覆盖 [i, p-1]）。
从右往左枚举 i，尝试让 [i, p-1] 成为一段：
用 qmx(i, p-1) 和 qmn(i, p-1) 求这段的最大值和最小值。
判断 max( (段max) - a[i-1], a[i-1] - (段min) ) <= x。
注意这里的 a[i-1]——它把下一段（左边相邻那段）的起点 a[i-1] 也纳入了考量。
让我仔细理解这个条件。条件判断的是：把 a[i-1] 与 [i, p-1] 这段拼在一起时的"范围"。若把 a[i-1] 也考虑进 [i,p-1] 这段，那么整段的极差就是 max(段max, a[i-1]) - min(段min, a[i-1])，也就是 max(段max - a[i-1], a[i-1] - 段min)。所以这个条件等价于：

a[i-1] 加入 [i, p-1] 这段后，新段的极差 ≤ x。
满足时就把 i-1 也并进来（p = i），继续向左扩展。否则 i-1 必须单独另起一段。

循环结束后，若 p == 1，说明能成功地从右往左把整段都覆盖完（最后一段能扩到最左端且都满足极差 ≤ x），返回 true；否则 false。
所以 ok(x) 本质上判定：能否把数组划分成若干段，每段（含相邻段的边界衔接点）的极差都不超过 x
读入。注意：cin >> n >> a[0] >> a[1]; n++，由于 a[i-1] 需要用到索引 0 和下标从 0 开始，这里把 n 加了 1、并把 a[0], a[1] 在外面先读，后续从 i=2 读到 i=n。实际数组长度为 n+1（索引 0..n）。
建立每个位置长度为 1 的初始表 mx[0][i]=mn[0][i]=a[i]。
递推建立最大/最小 Sparse Table（i 到 16，因为 N=1e5，2^17 > 1e5）。
二分下界 l = abs(a[0]-a[1])（至少是相邻首两元素的差值，因为答案不可能小于初始相邻差），上界 r = inf = 1e9。
标准二分求最小可行的 x。
输出 l（最小阈值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, inf = 1e9;

int mx[20][N];
inline int qmx(int l, int r) {
    int k = __lg(r-l+1);
    return max(mx[k][l], mx[k][r-(1<<k)+1]);
}

int mn[20][N];
inline int qmn(int l, int r) {
    int k = __lg(r-l+1);
    return min(mn[k][l], mn[k][r-(1<<k)+1]);
}

int n, a[N];
inline bool ok(int x) {
    int p = n+1;
    for (int i = n; i; --i)
        if (max(qmx(i, p-1)-a[i-1], a[i-1]-qmn(i, p-1)) <= x)
            p = i;
    return p == 1;
}

int main() {
    fast;
    cin >> n >> a[0] >> a[1]; n++;
    for (int i = 2; i <= n; ++i) cin >> a[i];
    for (int i = 0; i <= n; ++i) mx[0][i] = mn[0][i] = a[i];
    for (int i = 1; i < 17; ++i)
        for (int j = 1; j <= n-(1<<i)+1; ++j) {
            mx[i][j] = max(mx[i-1][j], mx[i-1][j+(1<<(i-1))]);
            mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<(i-1))]);
        }
    int l = abs(a[0]-a[1]), r = inf;
    while (l < r) {
        int mid = (l+r)>>1;
        ok(mid) ? r=mid : l=mid+1;
    }
    cout << l << '\n';
    return 0;
}