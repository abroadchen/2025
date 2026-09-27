//
// Created by Psy.C on 2026/9/27.
//
/**
给定一个 n × m 的平面上有 k 个点 (nx[i], ny[i])。目标是通过二分答案找到最小的边长 x，使得用若干个边长为 x 的正方形能覆盖所有目标点（check(x) 判断边长 x 是否可行），最后输出这个最小边长 ans
对每个目标点 (nx[i], ny[i])，以它为中心向上下左右各扩展 x，得到能覆盖到它的方形区域边界 [lx, rx] × [ly, ry]，并裁剪到地图范围 [1,n]×[1,m] 内。
把这些边界值（以及各自再±1 后的值）全部收集进 tx[]、ty[]，用于坐标离散化（压缩大量重复坐标，避免在巨大的 n×m 上直接开数组）
排序 + 去重，得到离散化后的唯一坐标集合，数量为 cnt 和 tot。
把每个点扩展后区域的边界 lx, rx, ly, ry 映射成离散化后的下标，之后在压缩后的网格上操作
在离散化网格上做二维差分（对每个覆盖区域矩形进行 add/del），再通过二维前缀和还原。
若某处 a[i][j] == 0，表示该格子没有被任何方形覆盖（即存在"空白/未覆盖点"）。
统计这些未覆盖格子的范围：横向 [l, r]、纵向 [d, u]
if (!r) return 1：若没发现任何未覆盖格子（所有目标点都被覆盖），直接返回可行（1）。
否则，找出"这些未覆盖点构成的空白矩形"的宽高，取半，得到要覆盖这个空白区域还需要的新方形边长 len（取横向、纵向两个方向较大的那个的一半）。
若这个 len <= x，说明用边长 x 的正方形足以再补上这个空白区域 → 可行；否则不可行
读入 n、m、k 及 k 个点的坐标。
在 [0, max(n,m)+1] 范围内对边长做二分查找：
check(mid) == true → 该边长可行，记录 ans = mid，往更小找（r = mid-1）；
否则往更大找（l = mid+1）。
最终输出能覆盖所有点所需的最小边长 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e3+10, inf = 0x7f7f7f7f;

int a[N][N], cnt, tot, tx[N], ty[N], n, m, k, lx[N], ly[N], rx[N], ry[N], nx[N], ny[N];
inline bool check(int x) {
    memset(a, 0, sizeof(a)); cnt = tot = 0;
    tx[++cnt] = 1, tx[++cnt] = n; ty[++tot] = 1, ty[++tot] = m;
    for (int i = 1; i <= k; ++i) {
        lx[i] = max(1, nx[i]-x), rx[i] = min(n, nx[i]+x);
        ly[i] = max(1, ny[i]-x), ry[i] = min(m, ny[i]+x);
        tx[++cnt] = lx[i], tx[++cnt] = rx[i], tx[++cnt] = max(1, lx[i]-1), tx[++cnt] = min(n, rx[i]+1);
        ty[++tot] = ly[i], ty[++tot] = ry[i], ty[++tot] = max(1, ly[i]-1), ty[++tot] = min(m, ry[i]+1);
    }
    sort(tx+1, tx+cnt+1), cnt = unique(tx+1, tx+cnt+1) - tx - 1;
    sort(ty+1, ty+tot+1), tot = unique(ty+1, ty+tot+1) - ty - 1;
    for (int i = 1; i <= k; ++i) {
        lx[i] = lower_bound(tx+1, tx+cnt+1, lx[i]) - tx, ly[i] = lower_bound(ty+1, ty+tot+1, ly[i]) - ty;
        rx[i] = lower_bound(tx+1, tx+cnt+1, rx[i]) - tx, ry[i] = lower_bound(ty+1, ty+tot+1, ry[i]) - ty;
    }
    int l = inf, r = 0, d = inf, u = 0;
    for (int i = 1; i <= k; ++i)
        ++a[lx[i]][ly[i]], --a[lx[i]][ry[i]+1], --a[rx[i]+1][ly[i]], ++a[rx[i]+1][ry[i]+1];
    for (int i = 1; i <= cnt; ++i)
        for (int j = 1; j <= tot; ++j) {
            a[i][j] = a[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
            if (!a[i][j])
                l = min(l, i), r = max(r, i), d = min(d, j), u = max(u, j);
        }
    if (!r) return 1;
    int len = max((ty[u] - ty[d] + 1) >> 1, (tx[r] - tx[l] + 1) >> 1);
    return len <= x;
}

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) cin >> nx[i] >> ny[i];
    int l = 0, r = max(n, m)+1, mid, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}