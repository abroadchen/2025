//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
区间数组 b，N = 1510 的上限
计算前缀和 s：s[i] 表示前 i 个位置中，有多少个元素满足 a[i] <= mid（即低于等于阈值 mid 的位置有权值 1，大于则权值 0）
f[1][i] = 只选第 i 个区间时，该区间内满足 a[j] <= mid 的贡献和。
f[i][j] = 选用 i 个区间覆盖，且最后一个区间是第 j 个时的最大总贡献。

转移的两种来源：

与上一段相连接（有重叠/相邻）‍：从队头 q[l]（与区间 j 可衔接的最大值）延伸，加上 s[b[j].r]-s[b[q[l]].r]（区间 j 在上一区间右侧新增的部分）。这里用前缀和把区间贡献化成了 O(1) 的 s[r]-s[l-1]。
与上一段完全不相交：取之前不与 j 重叠的区间 q[l] 里的最大值 mx，直接加上 s[b[j].r]-s[b[j].l-1]（区间 j 本身的贡献）。
用单调队列维护 f[i-1][x]-s[b[x].r] 的最大值，这一步把内层 j 的复杂度从 O(n²) 压到 O(n)。
若「恰用 m 个区间」能满足总贡献 ≥ k，则 mid 可行（实际上这里只检查了恰好 m 个，i 循环覆盖了最后一个区间位置）
去重：只保留右端点递增的区间（去掉完全被前面区间包含的区间），简化 DP。
m = min(m, n)：选的区间数不会超过总区间数。
对答案（阈值）做二分：若阈值 mid 可行，说明答案更小，左移；否则右移。
若最终 lo 超出上限说明无解，输出 -1


l, r 是单调队列 q 的头尾指针（q 里存的是区间下标，即上一层的候选 p）。
mx 记录已经滑出、与 j 不再相交的那些 p 中 f[i-1][p] 的最大值（这就是情况 B 需要的蓄水池
入队第 j-1 号区间（把它作为上一层候选 p 加入队列）。

我们要入队的是 p = j-1，它在队列里的"价值"按情况 A 的式子记作 f[i-1][p] - s[b[p].r]（因为转移时还要加 s[b[j].r]，而 s[b[j].r] 对同一 j 是常数，可先不算）。
单调队列维护的是：f[i-1][p] - s[b[p].r] 随队列从左到右递减。
这一步 while 即"移除队尾价值比新来者小的元素"，保证队列单调
队头出队判定：当队头的区间 q[l] 其右端点 b[q[l]].r < b[j].l 时，说明它已经和当前 j 完全不相交了。

既然后面 j 还会继续右移，q[l] 永远不会再与未来的 j 相交，它正式进入情况 B 的池子，把它 f[i-1][q[l]] 更新进 mx，然后弹出（++l）。
这正是上面注释说的"处理与当前区间不相交时的最大值"

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (ll i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 1510;
constexpr ll inf = 1e17;

struct node { ll l, r; } b[N];
bool cmp(node a, node b) { return a.l < b.l; }

ll L, s[N], a[N], f[N][N], n, m, l, r, q[N], k;
bool check(ll mid) {
    rep(i,1,L) s[i] = s[i-1] + (a[i] > mid ? 0 : 1);
    memset(f, 0xcf, sizeof f);
    rep(i,1,n) f[1][i] = s[b[i].r] - s[b[i].l-1];
    rep(i,2,m) {
        l = 1, r = 0;
        for (ll j = i, mx = -inf; j <= n; j++) {
            while (l <= r && f[i-1][j-1]-s[b[j-1].r] > f[i-1][q[r]]-s[b[q[r]].r]) --r;
            q[++r] = j - 1;
            while (l <= r && b[q[l]].r < b[j].l) { mx = max(mx, f[i-1][q[l]]); ++l; }
            f[i][j] = max((l<=r?s[b[j].r]-s[b[q[l]].r]+f[i-1][q[l]]:-inf), mx+s[b[j].r]-s[b[j].l-1]);
        }
    }
    rep(i,m,n) if (f[m][i] >= k) return 1;
    return 0;
}


int main() {
    fast;
    cin >> L >> n >> m >> k;
    rep(i,1,L) cin >> a[i];
    rep(i,1,n) cin >> b[i].l >> b[i].r;
    sort(b+1, b+1+n, cmp);
    ll tot = 0;
    rep(i,1,n) if (!tot || b[tot].r < b[i].r) b[++tot] = b[i];
    n = tot; m = min(m, n);
    ll lo = 1, hi = 1e9;
    while (lo <= hi) {
        ll mid = (lo + hi) >> 1;
        if (check(mid)) hi = mid-1; else lo = mid+1;
    }
    if (lo > 1e9) lo = -1;
    cout << lo;
    return 0;
}