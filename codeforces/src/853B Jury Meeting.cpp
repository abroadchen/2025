//
// Created by Psy.C on 2026/9/30.
//
/***
每个事件 a[i]：d 日期、f 起点、t 终点、c 费用。
st[u]：到某个中间点 u 的最小"出程费用"（阶段1，t==0 表示出程事件，其 t 字段其实是中间点）。
ed[u]：从某个中间点 u 出发的最小"回程费用"（阶段2，f==0 表示回程事件）。
f_arr[i]：前缀——表示在日期 ≤ i 内，n 个人全部完成出程所需的最小总费用。
g_arr[i]：后缀——表示在日期 ≥ i+k 内，n 个人全部完成回程所需的最小总费用
按日期排序，为后续扫描做准备
费用数组初始化为"极大值 × n"（因为要全 n 个人，默认不可行）。
st[] / ed[] 初始为 inf（还没找到任何班次
f_arr[i] 表示"所有人在日期严格小于 i 时完成出程的最小总费用"。
扫描日期 d < i 的出程事件（t==0，f 是中间点）：若 st[f] 的现有费用比 a[j].c 大，则用一个更便宜的事件替换，f_arr[i] 相应减掉差额。
维护 st[m点]：到该中间点的最便宜出程费用。遍历后 f_arr 是单调不减的前缀前缀最优累计
g_arr[i] 表示"所有人在日期 ≥ i+k 完成回程的最小总费用"。
倒序扫描日期 ≥ i+k 的回程事件（f==0，t 是中间点）：若 ed[t] 现有费用比 a[j].c 大则替换，g_arr[i] 减掉差额。
ed[m点]：从该中间点出发的最便宜回程费用。
关键约束体现在下标：出程必须在 < i，回程必须在 ≥ i+k，中间至少隔 k 天，所以枚举"分割点 i"
枚举每个分割点 i：前 i-1 天完成所有出程（费用 f_arr[i]），i+k 之后完成所有回程（费用 g_arr[i]），总费用相加，取最小。
若任一阶段不可行（保持 inf），ans 仍为 inf → 输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+10, M = 1e6+10, K = M-10;
constexpr ll inf = 1e12;

struct ft { ll d, f, t, c; } a[N];
bool cmp(const ft& x, const ft& y) { return x.d < y.d; }

template<typename T>
static T rd() {
    T f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll f[M], g[M], st[N], ed[N], ans;
int main() {
    fast;
    int n = rd<int>(), m = rd<int>(), k = rd<int>();
    for (int i = 1; i <= m; ++i)
        a[i].d = rd<ll>(), a[i].f = rd<ll>(), a[i].t = rd<ll>(), a[i].c = rd<ll>();
    sort(a+1, a+m+1, cmp);
    for (int i = 0; i <= K+1; ++i) f[i] = g[i] = 1ll*inf*n;
    for (int i = 1; i <= n; ++i) st[i] = ed[i] = inf;
    int j = 1;
    for (int i = 1; i <= K-k; ++i) {
        f[i] = f[i-1];
        while (j <= m && a[j].d < i) {
            if (!a[j].t && st[a[j].f] > a[j].c) {
                f[i] -= st[a[j].f] - a[j].c;
                st[a[j].f] = a[j].c;
            }
            ++j;
        }
    }
    j = m;
    for (int i = K-k; i >= 1; --i) {
        g[i] = g[i+1];
        while (j >= 1 && a[j].d >= i + k) {
            if (!a[j].f && ed[a[j].t] > a[j].c) {
                g[i] -= ed[a[j].t] - a[j].c;
                ed[a[j].t] = a[j].c;
            }
            --j;
        }
    }
    ans = inf;
    for (int i = 1; i <= K-k; ++i) ans = min(ans, f[i] + g[i]);
    if (ans == inf) cout << "-1\n"; else cout << ans << '\n';
    return 0;
}