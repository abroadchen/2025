//
// Created by Psy.C on 2026/9/13.
//
/**
按顺序把颜色放入当前段 res，vis[color] 记录该颜色最近一次所属段号；如果某个颜色在当前段已经出现过（vis==res），则跳过（同一颜色在同一段只算一次）。真正"新遇到"的不同颜色计数 cnt。
当一段内的不同颜色数 cnt > k，说明这段太长，开新段 res++。
返回 res+1 = 用该贪心规则需要的最少段数
get(k) 关于 k 单调不增（k 越大段数越少）。所以在区间 [l,r] 上：

先求两端：段数上限为 l 时需要的段数 lc，上限为 r 时需要段数 rc。
若 lc == rc：说明在这个区间内，无论段数上限取 l..r 的哪个值，最少段数都一样，于是整个区间 [l,r] 的答案统一填 lc（可以少算中间很多次 get）。这是分治的剪枝。
若 lc != rc：则 ans[l]=lc, ans[r]=rc，并递归处理中间 [l+1, mid] 和 [mid+1, r-1]。
这样对每个可能的"答案段数"基本只算一次 get，避免对每个 k 都 O(n) 扫一遍的 O(n²) 开销，整体接近 O(n log n)
数组下标 1..n 作为"段数上限 k"的可能取值（k 从 1 到 n）。
ans[k] 存：段数上限为 k 时，贪心能得到的最少段数。
输出 ans[1..n]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int vis[N], n, c[N];
int get(int k) {
    int res = 0, cnt = 0;
    memset(vis, -1, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        if (vis[c[i]] == res) continue;
        vis[c[i]] = res;
        cnt++;
        if (cnt > k) {
            res++;
            cnt = 1;
            vis[c[i]] =res;
        }
    }
    return res+1;
}

int ans[N];
void dfs(int l, int r) {
    if (l > r) return;
    int lc = get(l), rc = get(r);
    if (lc == rc) {
        for (int i = l; i <= r; ++i) ans[i] = lc;
        return;
    }
    ans[l] = lc; ans[r] = rc;
    int mid = (l+r)>>1;
    dfs(l+1, mid); dfs(mid+1, r-1);
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    dfs(1, n);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}