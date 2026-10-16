//
// Created by Psy.C on 2026/10/16.
//
/**
给定序列 a[1..n]，通过两类操作减少元素，问最少需要多少次操作把所有值消掉，并输出每次操作的位置。特征在于 DP 转移用 f[i-2] + a[i] 与 f[i-3] + max(a[i-1],a[i]) 两种状态，以及回溯时做了"取相邻两个、再取第三段"的贪心减除。

这是一个典型的"相邻配对 + 可隔一个跳跃"的覆盖贡献型 DP（类似条形图消去 / 两个人并排坐）
读入 n 个数，然后 n++（多开一位，作为哨兵，避免越界，配合 i+1、a[i+1] 的访问）
DP 状态 f[i]：处理到第 i 个元素的最优代价（最少操作数）。fr[i] 记录转移来源（用于回溯）。

两种转移：

默认：f[i] = f[i-2] + a[i]，来源 i-2。含义：跳过第 i-1 项，单独处理 a[i]。
可更新（当 i≥3）：f[i] = f[i-3] + max(a[i-1], a[i])，来源 i-3。含义：把第 i-1 和 i 两个相邻项"合并处理"，代价取两者较大值。
这里 DP 在选择相邻两项时，用 max 表示一次操作覆盖一对。整体是求覆盖整个序列所需的最少操作次数
从 i = n 开始沿 fr[i] 一路跳回。每一步按当前节点做三组"相邻配对减除"：

配对 (i-1, i)：取 min，把两者的公共部分减掉，记录位置 i-1。
配对 (i, i+1)：记录 i。
若来源是 i-3（说明用了第二种转移，即处理 (i-1,i) 的合并分支），额外配对 (i-2, i-1)，记录 i-2。
每次 d = min(...)，若为 0 则不做记录。这是贪心回溯：沿着 DP 最优路径，把每一步对应的相邻配对就地减去，实际还原出每个操作发生的位置
先输出操作次数（ans 大小），再逐行输出每次操作的位置。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 3e5+5;

int n, a[N], f[N], fr[N];
vector<int> ans;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i]; n++;
    for (int i = 1; i <= n; ++i) {
        f[i] = f[max(0ll, i-2)] + a[i], fr[i] = max(0ll, i-2);
        if (i >= 3 && f[i-3] + max(a[i-1], a[i]) < f[i])
            f[i] = f[i-3] + max(a[i-1], a[i]), fr[i] = i - 3;
    }
    for (int i = n; i; i = fr[i]) {
        int d = min(a[i-1], a[i]);
        if (d) {
            ans.push_back(i-1);
            a[i-1] -= d; a[i] -= d;
        }
        d = min(a[i], a[i+1]);
        if (d) {
            ans.push_back(i);
            a[i] -= d; a[i+1] -= d;
        }
        if (fr[i] == i-3) {
            d = min(a[i-2], a[i-1]);
            if (d) {
                ans.push_back(i-2);
                a[i-2] -= d; a[i-1] -= d;
            }
        }
    }
    cout << ans.size() << '\n';
    for (int x : ans) cout << x << '\n';
    return 0;
}