//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
对每个查询：
sz = r-l+1：本次差阈值。
pos = upper_bound(...)：c 里第一个大于 sz 的位置（1-based，c+1 起）。
计算答案：
mx+sz-mn：全局跨度基础上加一个 sz（合并室的扩展量）。
d[pos]：前 pos-1 个（≤ sz 的小差值）的和，减去。
(cnt-pos)*sz：之后所有大于 sz 的差值，每个都按 sz 计（它们都 >= sz，合并需要 sz 而非原差）。
这一行是核心公式：对差值 ≤ sz 的相邻对直接合并（浪费减少 d[pos]），对差值 > sz 的每个补 sz（把它们"拉近"到 sz 一起合并）。最终答案 = 最大跨度扩展后再修正
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr ll N = 2e5+5, inf = 1e18;

ll n, mx, mn = inf, a[N], b[N], c[N], d[N], q;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i], mx = max(mx,a[i]), mn = min(mn,a[i]);
    sort(a+1,a+n+1);
    int cnt = 0; a[0] = -inf;
    rep(i,n) if (a[i] != a[i-1]) b[++cnt] = a[i];//去重存到 b，cnt=不同值个数
    for (ll i = 2; i <= cnt; i++) c[i-1] = b[i] - b[i-1];//相邻差存入 c，共 cnt-1 个
    sort(c+1,c+cnt);
    for (ll i = cnt-1; i >= 1; i--) d[i] = d[i+1] + c[i];//从 i 到末尾的差值和（后缀和）
    cin >> q;
    while (q--) {
        ll l, r; cin >> l >> r;
        ll sz = r-l+1, pos = upper_bound(c+1,c+cnt,sz)-c;
        cout << mx+sz-mn-d[pos] + (cnt-pos)*sz << ' ';
    }
    return 0;
}