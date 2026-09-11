//
// Created by Psy.C on 2026/9/11.
//
/**
v[i] 存矩阵第 i 行（0 基准数组，v[0] 是哨兵行，全 0）。
n 行、m 列
为每一行 i 记录一个"临界起点" row[i]：

对每行 i，初始 row[i] = i。
对每一列 j：比较当前行值 cur=v[i][j] 与上一行值 pre=v[i-1][j]。
若 cur < pre（第 j 列在 i 行处发生下降），记 col[j] = i——即"第 j 列最后一次出现下降的行号"。
row[i] = min(row[i], col[j])：取所有列"最后一次下降行号"的最小值，作为该行 i 的 row[i]。
含义：row[i] = 在第 i 行及之前的行里，最早使得"某列发生下降"的那个行号（对所有列取最早者）。也就是说，从 row[i] 这一行开始往后，才可能出现某列非单调；在 row[i] 之前（行号更小处）的所有列都是严格/非严格单调不减的。

直观理解：row[i] 是所有列中"最近一次不满足单调的行号"的最小值。若某个区间 [l, r] 完全落在所有下降点之后且没有下降，矩阵在该区间在各列都单调
对询问 (l, r)：

row[r] 是"到第 r 行为止，某列最后一次发生下降的最小行号"。
若 row[r] > l：说明存在一列在行号 > l（即落入区间 [l, r]）处发生下降 → 该列在区间内不单调 → 输出 No。
否则（row[r] <= l）：所有列的下降都发生在第 l 行之前，区间 [l, r] 内每列单调不减 → 输出 Yes
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+10;
vector<int> v[N];
int row[N], col[N];
int main() {
    fast;
    int n, m, x; cin >> n >> m;
    for (int i = 0; i < m; ++i) v[0].push_back(0);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> x, v[i].push_back(x);
    for (int i = 1; i <= n; ++i) {
        row[i] = i;
        for (int j = 0; j < m; ++j) {
            int cur = v[i][j], pre = v[i-1][j];
            if (cur < pre) col[j] = i;
            row[i] = min(row[i], col[j]);
        }
    }
    int t; cin >> t;
    while (t--) {
        int l, r; cin >> l >> r;
        if (row[r] > l) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}