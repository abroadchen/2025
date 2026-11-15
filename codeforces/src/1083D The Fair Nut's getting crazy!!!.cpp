//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
离散化去重。
L[i]：从前往后扫，L[i] = 前一个值与 a[i] 相同的位置 +1（使得区间左端 ≥ L[i] 时 a[i] 在该值的区间内首次出现）。
R[i]：从后往前扫，R[i] = 下一个同名位置 −1（右端 ≤ R[i] 时 a[i] 是最后一次出现）。
窗口 [l,r] 内值全部互不相同 ⟺ 对 ∀i∈[l,r] 有 L[i]≤l 且 R[i]≥r（经典"无重复子数组"判定）。这正好和后面单调栈维护的两个约束对应
对应每个区间维护：mx（max 之和）、mn（min 之和）、mi（带位置的某种和）、ml（交叉项）。+ 运算逐项取模相加
tr[k].mx：对"最大值"池的区间加法标记。
tr[k].mn：对"最小值"池的区间加法标记
pushmn(k, v)（给最小值整体加 v）pushmx(k, v)（给最大值整体加 v）
这里 S(x)=x(x+1)/2 是 Σ 前 x 的位置和
含义：区间内所有位置的"最大/最小"同时加 v 时，mx、mn、ml、mi 的更新通过交叉项 ml（= Σ max·min）和位置和 mi 联动维护
用两个单调栈分别保证"每列的 max 值（L 相关）和 min 值（R 相关）"在滑动中的正确区间，通过区间改写维护线段树里每个位置的 mx、mn 分量。
每次对 [pos, i] 区间 query，得到四个聚合值后套入一个数学表达式计算 tmp，累加进 ans。
核心思想：枚举右端点 i，维护以 i 为右端的所有合法左端点，用双单调栈保证窗口边界（无重复 / 条件），线段树维护窗口内每个位置的 mx、mn、及位置加权和，最终把「Σ 某种形式的区间权值」用多项式公式一次性算出来
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, mod = 1e9+7;

inline int add(ll x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}
inline void inc(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}
inline int mul(ll x, ll y) { return x*y%mod; }
inline int dec(ll x, ll y) {
    x -= y;
    if (x < 0) x += mod;
    return x%mod;
}
inline ll S(int x) { return 1ll*x*(x+1)/2; }

namespace sgt {
    struct node {
        ll mx, mn, mi, ml;
        friend node operator+(const node& a, const node& b) {
            return {add(a.mx,b.mx), add(a.mn,b.mn),
                add(a.mi,b.mi), add(a.ml, b.ml)};
        }
    };
    struct seg { int l, r; node t; ll mx, mn; } tr[N<<2];
#define ls tr[k].l
#define rs tr[k].r
#define mid ((ls+rs)>>1)
    void push_up(int k) { tr[k].t = tr[k<<1].t + tr[k<<1|1].t; }
    void pushmn(int k, int v) {
        inc(tr[k].mn, v);//mn += v（每个位置 min 加 v，区间长 1
        inc(tr[k].t.ml, mul(v, tr[k].t.mx));//ml += v·mx
        inc(tr[k].t.mn,mul(v, rs-ls+1));//t.mn += v·长度
        inc(tr[k].t.mi, mul(v, dec(S(rs), S(ls-1))));//mi += v·(Σ 位置 = S(rs)-S(ls-1))
    }
    void pushmx(int k, int v) {
        inc(tr[k].mx, v);
        inc(tr[k].t.ml, mul(v, tr[k].t.mn));//ml += v·mn
        inc(tr[k].t.mx, mul(v, rs-ls+1));//t.mx += v·长度
    }
    void push_down(int k) {
        if (tr[k].mx) {
            pushmx(k<<1, tr[k].mx); pushmx(k<<1|1, tr[k].mx);
            tr[k].mx = 0;
        }
        if (tr[k].mn) {
            pushmn(k<<1, tr[k].mn); pushmn(k<<1|1, tr[k].mn);
            tr[k].mn = 0;
        }
    }
    void build(int k, int l, int r) {
        ls = l; rs = r; tr[k].mx = tr[k].mn = 0; tr[k].t = {0,0,0,0};
        if (l == r) return;
        build(k<<1, l, mid); build(k<<1|1, mid+1, r);
    }
    void modify(int k, int l, int r, int v, int op) {
        if (rs < l || ls > r) return;
        if (l <= ls && rs <= r) return op ? pushmx(k,v) : pushmn(k,v);
        push_down(k);
        if (r <= mid) modify(k<<1, l, r, v, op);
        else if (l > mid) modify(k<<1|1, l, r, v, op);
        else modify(k<<1,l,mid,v,op), modify(k<<1|1,mid+1,r,v,op);
        push_up(k);
    }
    node query(int k, int l, int r) {
        if (rs < l || ls > r) return {0,0,0,0};
        if (l <= ls && rs <= r) return tr[k].t;
        push_down(k);
        if (r <= mid) return query(k<<1, l, r);
        if (l > mid) return query(k << 1 | 1, l, r);
        return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
    }
}
using namespace sgt;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], b[N], cnt, L[N], R[N], t[N], tx, tn, stx[N], stn[N];
ll ans;
int main() {
    fast;
    n = rd(); build(1, 1, n);
    rep(i,n) a[i] = b[i] = rd();
    sort(b+1, b+n+1);
    cnt = unique(b+1, b+n+1) - b - 1;
    rep(i,n) a[i] = lower_bound(b+1,b+cnt+1,a[i]) - b;
    rep(i,n) { L[i] = t[a[i]] + 1; t[a[i]] = i; }//L[i]=上一个同名值的位置+1
    rep(i,cnt) t[i] = n+1;
    for (int i = n; i; i--) { R[i] = t[a[i]]-1; t[a[i]] = i; }//R[i]=下一个同名值的位置−1
    int pos = 1;
    rep(i,n) {
        while (tx && L[i] >= L[stx[tx]])//维护 L 的单调递减栈 stx，弹出时把"变大"的 L 回滚
            modify(1,stx[tx-1]+1,stx[tx],dec(0,L[stx[tx]]),1), --tx;
        modify(1,stx[tx]+1,i,L[i],1);//把区间 [stx[tx]+1, i] 的"最大值"设为 L[i]（op=1 走 pushmx）
        stx[++tx] = i;
        while (tn && R[i] <= R[stn[tn]])//维护 R 的单调递增栈 stn，同理 op=0 走 pushmn
            modify(1,stn[tn-1]+1,stn[tn],dec(0,R[stn[tn]]),0), --tn;
        modify(1,stn[tn]+1,i,R[i],0);
        stn[++tn] = i;
        pos = max(pos, L[i]);
        node res = query(1,pos,i);
        ll tmp = dec(add(res.mi,mul(i,res.mx)),
            add(res.ml,mul(dec(S(i),S(pos-1)),i)));
        inc(ans, tmp);
    }
    cout << ans;
    return 0;
}