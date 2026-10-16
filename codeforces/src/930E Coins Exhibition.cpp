//
// Created by Psy.C on 2026/10/16.
//
/**
输入 n 个 A 类区间、m 个 B 类区间的左右端点。
关键技巧：左端点存 --l（左端点减 1），配合右端点 r，收集所有关键坐标到 p[]，再加上 0 和 k。
排序去重得到离散化坐标数组。这一步把"区间 [l,r]"变成"离散坐标 a.l 到 a.r 之间连续的一段坐标区间"（用左端点减 1 是为了让区间在离散下标上左闭右开/连续），方便后面切分
rg[i][0]：所有左端点 ≥ i 的 A 类区间中，最小的右端点。
rg[i][1]：同理为 B 类。
第 2、3 个循环先把每个区间在"它左端点处"记录最小右端点，最后一个后缀循环从右往左把"更靠右的左端点"的最小右端点也滚进来。

这样 rg[i][0] 就表示"从位置 i 开始往右，第一个 A 类限制区间的右端在哪"——用于判断某个切分点是否会被某类区间"穿过/覆盖"
DP 状态 f[i][s] 表示"从离散坐标 i 开始到末尾，处于状态 s 时的方案数"。三个状态通常代表：

s=0：当前"开放段"尚未被 A 类区间触碰过（当前这一段不允许包含 A 类限制区间）。
s=1：当前段未被 B 类区间触碰过（不允许包含 B 类限制区间）。
s=2：当前段两类的限制都还"安全/不受约束"（可自由切分）。
（有的写法把 0/1 解释为"目前段会违反 A / 会违反 B"，2 为中性的自由状态，具体语义看原题。代码只能确认存在三种互相转化的状态。）

转移辅助量 g[]
g[2]：
从自由状态 i+1 往前，坐标区间 (p[i], p[i+1]] 内部可以任意切分（不含两端点作为强制切分点），其中"完全不切"和"整体一段"被单独处理。
长度为 len = p[i+1]-p[i] 的区间内部任意切分方式数是 2^(len)（每个内部缝隙可切或不切），减去 2 是去掉"一种全切过头的情况"，具体取决于定义。总之它为状态 2 提供"二叉树式任意划分"的方案数权。
g[0]、g[1]
这两项解决"某类限制区间的右端点超过当前可以自由切的位置"的问题：从 i+1 状态延续到 rg[i][j]（该类第一个限制的右端点）之前，状态保持一致；超过右端点后的方案要从总数里减去（f[i+1][j] - f[rg[i][j]][j]），从而把"会被该限制区间覆盖的段"排除掉
f[i][0]（未触 A）：从 f[i+1][0] 延续，或进入 B 类未触状态 g[1]，或进入自由状态 g[2]。
f[i][1] 对称。
f[i][2]：只能由 g[0]、g[1]、g[2] 组合，表示新的"自由/中性"段
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

constexpr int N = 4e5+5, mod = 1e9+7;

struct node { int l, r; } a[N], b[N];

int ksm(int x, int y) {
    int res = 1;
    while (y) {
        if (y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}

int k, n, m, p[N], t, rg[N][2], f[N][3], g[3];
int main() {
    fast;
    cin >> k >> n >> m;
    rep(i,1,n) cin >> a[i].l >> a[i].r, p[++t] = --a[i].l, p[++t] = a[i].r;
    rep(i,1,m) cin >> b[i].l >> b[i].r, p[++t] = --b[i].l, p[++t] = b[i].r;
    p[++t] = 0; p[++t] = k;
    sort(p+1, p+t+1); t = unique(p+1, p+t+1) - p - 1;
    rep(i,1,t) rg[i][0] = rg[i][1] = t + 1;
    rep(i,1,n) {
        a[i].l = lower_bound(p+1, p+t+1, a[i].l) - p;
        a[i].r = lower_bound(p+1, p+t+1, a[i].r) - p;
        rg[a[i].l][0] = min(rg[a[i].l][0], a[i].r);
    }
    rep(i,1,m) {
        b[i].l = lower_bound(p+1, p+t+1, b[i].l) - p;
        b[i].r = lower_bound(p+1, p+t+1, b[i].r) - p;
        rg[b[i].l][1] = min(rg[b[i].l][1], b[i].r);
    }
    per(i,t-1,0) rg[i][0] = min(rg[i][0], rg[i+1][0]), rg[i][1] = min(rg[i][1], rg[i+1][1]);
    f[t][0] = f[t][1] = f[t][2] = 1;
    per(i,t-1,1) {
        g[2] = 1ll*f[i+1][2]*(ksm(2,p[i+1]-p[i])-2+mod)%mod;
        rep(j,0,1) g[j] = (1ll*f[i+1][j]-f[rg[i][j]][j]+mod)%mod;
        f[i][0] = (1ll*f[i+1][0]+g[1]+g[2])%mod;
        f[i][1] = (1ll*f[i+1][1]+g[0]+g[2])%mod;
        f[i][2] = (1ll*g[0]+g[1]+g[2])%mod;
    }
    cout << f[1][2] << '\n';
    return 0;
}