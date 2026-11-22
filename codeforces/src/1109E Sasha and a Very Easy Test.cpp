//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
因为 mod 不一定质数，不能用费马小定理 u^(mod-2)；只要
gcd(u,mod)=1，扩展欧几里得就能求出逆元
N：节点数上限。
cnt：mod 的互异质因子个数。
e[i]：初始数组值。
pr[20]：存 mod 的所有互异质因子
t[u].sum：区间的实际和（取模）。
t[u].tag：乘法懒标记（整区间乘的数）。
t[u].val：类似"乘到区间上的其余质因子乘积"，用于配合 fac 精确维护除法。
fac[u][i]：区间 u 当前的质因子 i 的总指数（用于除法时精确约分）
上传：两个子的和相加取模。注意 val/tag/fac 在这里不需要合并——因为 sum 才是查询对象，val 是局部除法用的，节点自身懒标记不下传时 sum 已含全部量
把父节点的乘法懒标记传给两个子：子节点的 sum、tag、val 都乘上父节点的 tag/val。
把父节点累积的质因子指数 fac[u][i] 加到两个子节点上，然后清零。
因为乘法对取模是相容的（(sum×tag)mod），可以延迟到查询真正需要时再下传
叶子节点：
sum = e[l] % mod。
把 e[l] 中所有属于 pr[] 的质因子完全拆出，指数累加到 fac[u][i]，剩余部分存 val。
内部节点递归建树后 push_up。
关键点：每个值是"质因子部分（存 fac）+ 非质因子剩余乘积（存 val）"的组合，sum = 剩余 val × 各质因子^指数，但 sum 直接存的是最终取模值
区间乘法操作（op==1，对 [l,r] 乘 x）：
直接覆盖整个区间时：sum 和 tag 乘 x；从 x 中拆出所有质因子加入 fac[u][i]，剩余非质因子部分乘进 val。
否则 push_down 后递归两边，再 push_up
单点除以 x（op==2，对位置 pos（l==r）除以 x，即原题 op==2 只给一个单点）：
先约分质因子：把 x 里包含的 pr[i] 从对应 fac[u][i] 中减去（除以质因子是不用求逆元的，直接降指数）。
剩余部分 x（不含任何 pr 质因子，与 mod 互质）用 inv(x) 求模逆乘进 val。
最后把 sum 重新算：val × ∏ pr[i]^fac[u][i]。
因为质因子部分已精确整除、剩余部分与 mod 互质可求逆，所以即使 mod 非质数也能正确完成"除以 x"
标准区间查询：完全覆盖返回 sum，否则 push_down 后递归两边累计取模。
输入 n 和 mod，对 mod 分解质因数（只取互异质因子存入 pr[1..cnt]）。这就是后面除法约分所依据的质因子集合。
读入初始数组 e，建树。
读入操作数 m，循环处理三种操作：
op==1：区间乘法（还要读 x）。
op==2：单点除法（用 l 作为单点位置，r 忽略）。
op==3：区间求和并输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

inline int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int g = exgcd(b,a%b,x,y);
    int t = x; x = y; y = t-a/b*y;
    return g;
}

int mod;
inline int inv(int u) {
    int x, y; exgcd(u,mod,x,y);
    return (x%mod + mod)%mod;
}
inline int ksm(int x, int y) {
    int ans = 1;
    while (y) {
        if (y&1) ans = ans*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return ans;
}

constexpr int N = 1e5+10;

int cnt, e[N], pr[20];
struct sgt {
#define ls u<<1
#define rs (u<<1|1)
    struct node { int l, r, val, sum, tag; } t[N<<2];
    int fac[N<<2][20];
    void push_up(int u) { return t[u].sum = (t[ls].sum+t[rs].sum)%mod, void(); }
    void push_down(int u) {
        t[ls].sum = t[ls].sum*t[u].tag%mod; t[ls].tag = t[ls].tag*t[u].tag%mod; t[ls].val = t[ls].val*t[u].val%mod;
        t[rs].sum = t[rs].sum*t[u].tag%mod; t[rs].tag = t[rs].tag*t[u].tag%mod; t[rs].val = t[rs].val*t[u].val%mod;
        t[u].tag = t[u].val = 1;
        rep(i,cnt) { fac[ls][i] += fac[u][i]; fac[rs][i] += fac[u][i]; fac[u][i] = 0; }
    }
    void build(int u, int l, int r) {
        t[u].l = l, t[u].r = r, t[u].tag = 1, t[u].val = 1;
        if (l == r) {
            t[u].sum = e[l]%mod;
            int x = e[l];
            rep(i,cnt) while (x%pr[i] == 0) fac[u][i]++, x /= pr[i];
            t[u].val = x%mod;
            return;
        }
        int mid = (l+r)>>1;
        build(ls, l, mid); build(rs,mid+1, r);
        push_up(u);
    }
    void upd(int u, int l, int r, int val) {
        if (t[u].l >= l && t[u].r <= r) {
            t[u].sum = t[u].sum*val%mod; t[u].tag = t[u].tag*val%mod;
            rep(i,cnt) while (val%pr[i] == 0) fac[u][i]++, val /= pr[i];
            t[u].val = t[u].val*val%mod;
            return;
        }
        push_down(u);
        int mid = (t[u].l + t[u].r) >> 1;
        if (l <= mid) upd(ls, l, r, val);
        if (r > mid) upd(rs, l, r, val);
        push_up(u);
    }
    void upd2(int u, int pos, int x) {
        if (t[u].l == t[u].r) {
            rep(i,cnt) while (x%pr[i] == 0) fac[u][i]--, x /= pr[i];
            t[u].sum = t[u].val = t[u].val*inv(x)%mod;
            rep(i,cnt) t[u].sum = t[u].sum*ksm(pr[i],fac[u][i])%mod;
            return;
        }
        push_down(u);
        int mid = (t[u].l + t[u].r) >> 1;
        if (pos <= mid) upd2(ls, pos, x); else upd2(rs, pos, x);
        push_up(u);
    }
    int qry(int u, int l, int r) {
        if (t[u].l >= l && t[u].r <= r) return t[u].sum;
        push_down(u);
        int mid = (t[u].l + t[u].r) >> 1, sum = 0;
        if (l <= mid) sum += qry(ls,l,r), sum %= mod;
        if (r > mid) sum += qry(rs,l,r), sum %= mod;
        return sum;
    }
} tr;

int n, m;
signed main() {
    fast;
    cin >> n >> mod;
    int v = mod;
    for (int i = 2; i <= v/i; i++) {
        if (v%i) continue;
        pr[++cnt] = i;
        while (v%i == 0) v /= i;
    }
    if (v > 1) pr[++cnt] = v;
    rep(i,n) cin >> e[i];
    tr.build(1,1,n);
    cin >> m;
    while (m--) {
        int op, l, r, x; cin >> op >> l >> r;
        if (op == 1) cin >> x, tr.upd(1,l,r,x);
        if (op == 2) tr.upd2(1,l,r);
        if (op == 3) cout << tr.qry(1,l,r)%mod << '\n';
    }
    return 0;
}