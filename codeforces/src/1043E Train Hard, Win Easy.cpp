//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
三个 BIT：t1（计数），t2（累加 a），t3（累加 b）。
qry(x) = 下标 ≤ x 的贡献和；qry2(x) = 下标 > x 的贡献和
对差值 a[i]-b[i] 排序去重，得到离散化映射 p = lower_bound(...)
把每个元素按其差值的离散化排名 p 插入三个 BIT
对每个元素 i，暂时移除自己，然后计算它与其他所有元素的某种配对代价之和：

对差值 ≤ p 的 j（即 a[j]-b[j] ≤ a[i]-b[i]）：
t1.qry(p)*b[i] + t2.qry(p) = (个数)·b[i] + Σa[j]
可整理为 Σ_j (a[j] + ...)，具体是 Σ a[j] + cnt·b[i]。
对差值 > p 的 j：
t1.qry2(p)*a[i] + t3.qry2(p) = (个数)·a[i] + Σb[j] = Σ b[j] + cnt·a[i]。
这是经典的"用符号判别配对代价"技巧：当 a[j]-b[j] ≤ a[i]-b[i] 时，配对代价取某一种表达式；否则取另一种。通常是求 "Σ_j min(某线性式)" 或"绝对值/与之差相关的割边计数"
对 m 对特殊限制关系 (x,y)，从 ans[x] 和 ans[y] 中各自减去 min(a[x]+b[y], a[y]+b[x])。
说明这些对原本被错误地计为配对（或不该配对）‍，需要减去二者间本不该计算的配对代价，用该 min 值修正
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
#define low_bit(x) ((x)&-(x))
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

int n;
struct node {
    ll tr[N];
    void upd(int x, int y) { while (x <= n) tr[x] += y, x += low_bit(x); }
    ll qry(int x) {
        ll res = 0;
        while (x) res += tr[x], x -= low_bit(x);
        return res;
    }
    ll qry2(int x) { return qry(n) - qry(x); }
} t1, t2, t3;

int m, a[N], b[N], c[N];
ll ans[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i] >> b[i], c[i] = a[i] - b[i];
    sort(c+1, c+n+1);
    int k = unique(c+1, c+n+1) - c - 1;
    rep(i,n) {
        int p = lower_bound(c+1, c+k+1, a[i]-b[i]) - c;
        t1.upd(p,1), t2.upd(p,a[i]), t3.upd(p,b[i]);
    }
    rep(i,n) {
        int p = lower_bound(c+1, c+k+1, a[i]-b[i]) - c;
        t1.upd(p,-1), t2.upd(p,-a[i]), t3.upd(p,-b[i]);//先把 i 从树中移除（排除自己）
        ans[i] = t1.qry(p)*b[i] + t2.qry(p);//对差值更小(≤p)的元素贡献
        ans[i] += t1.qry2(p)*a[i] + t3.qry2(p);//// 对差值更大(>p)的元素贡献
        t1.upd(p,1), t2.upd(p,a[i]), t3.upd(p,b[i]);//重新插回
    }
    rep(i,m) {
        int x, y; cin >> x >> y;
        ans[x] -= min(a[x]+b[y], a[y]+b[x]);
        ans[y] -= min(a[x]+b[y], a[y]+b[x]);
    }
    rep(i,n) cout << ans[i] << ' ';
    return 0;
}