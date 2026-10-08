//
// Created by Psy.C on 2026/10/8.
//
/**
线段树维护某个前缀最小值，用于区间快速查"是否存在 前缀和 < 某阈值"。
外层 solve()：读入参数，构建数组，二分扫描事件，找到结果 t
线段树每个节点存区间内 cnt 的最小值。
query(L,R,...,k)：查询区间 [L,R] 内是否存在某个 cnt < k，若是则置全局标志 x=0。
x 用作"是否全部 ≥ k"的判定（初始 x=1，发现任一小于则清 0）
arr：各事件时间；x 标记是增益还是减益。
num[] 存每次的增量；cnt[] 累加成前缀和（用于后续线段树建树和区间查询）
用 upper_bound 在排序好的 arr 中找到时间 < k 的事件范围 [1, y-1]，逐一检查到这些时刻前缀和是否变负（sum + cnt[i] < 0）。
若全部不触发负值，直接输出 0（表示从头开始也安全，答案 0）
建树后，从第 1 个事件起逐个做：
sum += num[i] 累计存量；
若累计变负或有答案则提前停；
upper_bound 找到下一批在 arr[i]+k 时间范围内的事件 [i+1, y-1]；
query 检查这一段前缀和是否都 ≥ cnt[i]-sum（阈值）；若安全则 t=arr[i]+1。
最终输出最早导致不安全的触发时刻 t
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e6+1e2;
constexpr ll inf = 1e16;
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)

ll ans[N];
void push_up(ll p) { ans[p] = min(ans[ls(p)], ans[rs(p)]); }

ll cnt[N];
void build(ll l, ll r, ll p) {
    if (l == r) { ans[p] = cnt[l]; return; }
    ll mid = (l + r) >> 1;
    build(l, mid, ls(p)); build(mid+1, r, rs(p));
    push_up(p);
}

ll x;
void query(ll L, ll R, ll l, ll r, ll p, ll k) {
    if (L <= l && r <= R) {
        if (ans[p] < k) x = 0;
        return;
    }
    ll mid = (l + r) >> 1;
    if (L <= mid) query(L, R, l, mid, ls(p), k);
    if (R > mid) query(L, R, mid+1, r, rs(p), k);
}

ll n, a, b, c, d, sum, k, arr[N], num[N], y, t;
void solve() {
    cin >> n >> a >> b >> c >> d >> sum >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i] >> x;
        if (x == 1) { num[i] = a; cnt[i] = c; }
        else { num[i] = -b; cnt[i] = -d; }
        cnt[i] += cnt[i-1];
    }
    x = 1; y = upper_bound(arr, arr+2+n, k-1) - arr;
    for (int i = 1; i < y; ++i)
        if (sum + cnt[i] < 0) x = 0;
    if (x) { cout << "0\n"; return; }
    build(1, n, 1);
    x = 1; arr[n+1] = inf; t = -1;
    for (int i = 1; i <= n; ++i) {
        sum += num[i];
        if (sum < 0 || t >= 0) break;//已变负或已有答案则停
        x = 1; y = upper_bound(arr, arr+2+n, arr[i]+k) - arr;
        query(i+1, y-1, 1, n, 1, cnt[i]-sum);//检查后续区间前缀和是否跌破 (cnt[i]-sum)
        if (x) { t = arr[i] + 1; break; }//安全 → 该时间作为答案
        if (i == n) t = arr[i] + 1;
    }
    cout << t << '\n';
}

int main() {
    fast;
    int q = 1;
    while (q--) solve();
    return 0;
}