//
// Created by Psy.C on 2026/9/21.
//
/**
把数组分成每块大小约 (M-3)=317 的若干块，L/R 记录每块左右边界
cnt[i][v]：前 i 块中值 v 的出现总次数（块级前缀和，便于 O(1) 求某值在某区间块内的出现次数）。
f[i][i]：第 i 块内高频数个数。
g[i][i]：第 i 块内高频数的总计数（超出部分累加）
用 DP 方式合并 f[i][j]、g[i][j]（块 i..j 的高频数统计）。
新增第 j 块时，检查新加入的值是否使累计超过 k，从而更新 f（高频个数）和 g（高频总计数
同块直接暴力：统计 tot，每数贡献 min(tot,k)
统计左右两端散块的 tot。
all：中间完整块(lb+1..rb-1)的元素总数减去其中高频数的"超出"计数，得到中间块的"常规贡献部分"
对每个散块中的值 a[i]，其总出现 = 散块贡献 + 中间整块贡献。
若合并后超过 k（高频），若中间部分本身 ≤ k，则把中间部分从 all 中移到高频贡献 k；否则维持。
右侧散块做同样处理
最后：中间整块的高频数 f 个，每个贡献 k；加上常规部分 all；再加散块已处理的贡献 = 最终 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 320;

int b, n, L[N], R[N], cnt[M][N], be[N], a[N], k, f[M][M], g[M][M];
void init() {
    b = (n-1)/(M-3) + 1;
    for (int i = 1; i <= b; ++i)
        L[i] = R[i-1]+1, R[i] = i*(M-3);
    R[b] = n;
    for (int i = 1; i <= b; ++i) {
        memcpy(cnt[i], cnt[i-1], sizeof*cnt);//继承上一块的计数
        for (int j = L[i]; j <= R[i]; ++j) {
            be[j] = i; ++cnt[i][a[j]];
        }
        for (int j = 1; j <= N-5; ++j)
            if (cnt[i][j]-cnt[i-1][j] > k)
                ++f[i][i], g[i][i] += cnt[i][j] - cnt[i-1][j];
    }
    static bool vis[N];
    for (int i = 1; i < b; ++i)
        for (int j = i+1; j <= b; ++j) {
            int& f = ::f[i][j], &g = ::g[i][j];
            f = ::f[i][j-1], g = ::g[i][j-1];//继承子区间
            for (int p = L[j]; p <= R[j]; ++p)
                if (cnt[j][a[p]]-cnt[i-1][a[p]] > k && !vis[a[p]]) {
                    vis[a[p]] = true;
                    if (cnt[j-1][a[p]]-cnt[i-1][a[p]] <= k) {
                        ++f;
                        g += cnt[j][a[p]]-cnt[i-1][a[p]];
                    } else g += cnt[j][a[p]]-cnt[j-1][a[p]];
                }
            for (int p = L[j]; p <= R[j]; ++p) vis[a[p]] = false;
        }
}

int m, tot[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i]; init();
    int ans = 0;
    for (cin >> m; m--; ) {
        int l, r; cin >> l >> r; l = (l+ans)%n+1, r = (r+ans)%n+1;//上一轮答案 ans 参与本轮 l、r 的异或/取模解码
        if (l > r) l^=r^=l^=r;
        ans = 0;
        if (be[l] == be[r]) {
            for (int i = l; i <= r; ++i) ++tot[a[i]];
            for (int i = l; i <= r; ++i) {
                if (tot[a[i]] > k) ans += k;
                else ans += tot[a[i]];
                tot[a[i]] = 0;
            }
            cout << ans << '\n';
        } else {
            int lb = be[l], rb = be[r];
            for (int i = l; i <= R[lb]; ++i) ++tot[a[i]];
            for (int i = L[rb]; i <= r; ++i) ++tot[a[i]];
            int all = R[rb-1]-R[lb]-g[lb+1][rb-1];
            for (int i = l; i <= R[lb]; ++i)
                if (tot[a[i]]) {
                    if (tot[a[i]]+cnt[rb-1][a[i]]-cnt[lb][a[i]] > k) {
                        if (cnt[rb-1][a[i]]-cnt[lb][a[i]] <= k) {
                            all -= cnt[rb-1][a[i]]-cnt[lb][a[i]];
                            ans += k;
                        }
                    } else ans += tot[a[i]];
                    tot[a[i]] = 0;
                }
            for (int i = L[rb]; i <= r; ++i)
                if (tot[a[i]]) {
                    if (tot[a[i]]+cnt[rb-1][a[i]]-cnt[lb][a[i]] > k) {
                        if (cnt[rb-1][a[i]]-cnt[lb][a[i]] <= k) {
                            all -= cnt[rb-1][a[i]]-cnt[lb][a[i]];
                            ans += k;
                        }
                    } else ans += tot[a[i]];
                    tot[a[i]] = 0;
                }
            ans += f[lb+1][rb-1]*k + all;
            cout << ans << '\n';
        }
    }
    return 0;
}