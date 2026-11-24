//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
sum：区间乘积（取模）。
mul：乘法懒标记。
st：位掩码，第 i 位=1 表示区间乘积包含质数 b[i]。
cov：位掩码懒标记（记录待下传的质因子集合）
300 以内有 62 个质数，分别存到 b[]，并预计算其模逆元 inv
M=70，1ll<<62 放得下。
叶子节点存初值 a[l]，并扫描 62 个质数，若 a[l] 含质因子 b[i] 则置位掩码
父节点 sum = 左右乘积取模；质因子 = 左右位或
mul（乘数）与 cov（质因子 OR 掩码）分别下传
区间每个数乘 x：sum 乘上 x^len
遍历 62 个质数，若 x 能被 b[i] 整除，就把该质因子加入掩码（st 和 cov）
返回该区间的 {sum, st}
遍历位掩码中所有置位质数，逐一乘 (p−1)⋅inv[p] 即可
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 4e5+5, mod = 1e9+7, M = 70;

struct node { int l, r, sum, mul; ll st, cov; } tr[N<<2];

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return res;
}

bool ispr(int x) {
    if (x <= 1) return 0;
    for (int i = 2; i <= x/i; i++)
        if (x%i == 0) return 0;
    return 1;
}

void push(node &u, node l, node r) {
    u.sum = 1ll*l.sum*r.sum%mod;
    u.st = l.st|r.st;
}
void push_up(int u) { push(tr[u], tr[u<<1], tr[u<<1|1]); }

int a[N], cnt, b[M];
void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, a[l], 1};
        for (int i = 0; i < cnt; i++)
            if (a[l]%b[i] == 0) tr[u].st |= 1ll<<i;
        return;
    }
    tr[u] = {l,r,0,1};
    int mid = (l+r)>>1;
    build(u<<1,l,mid), build(u<<1|1,mid+1,r);
    push_up(u);
}
void upd(node &u, int x) {
    u.sum = 1ll*u.sum*ksm(x,u.r-u.l+1)%mod;
    u.mul = 1ll*u.mul*x%mod;
}
void upd2(node &u, ll x) { u.st |= x; u.cov |= x; }

void push_down(int u) {
    auto &rt = tr[u], &l = tr[u<<1], &r = tr[u<<1|1];
    if (rt.mul != 1) { upd(l,rt.mul); upd(r,rt.mul); rt.mul = 1; }
    if (rt.cov) { upd2(l,rt.cov); upd2(r,rt.cov); rt.cov = 0; }
}
void modify(int u, int l, int r, int x) {
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].sum = 1ll*tr[u].sum*ksm(x,tr[u].r-tr[u].l+1)%mod;
        tr[u].mul = 1ll*tr[u].mul*x%mod;
        for (int i = 0; i < cnt; i++) if (x%b[i] == 0) {
            tr[u].st |= 1ll<<i; tr[u].cov |= 1ll<<i;
        }
        return;
    }
    push_down(u);
    int mid = (tr[u].l + tr[u].r)>>1;
    if (l <= mid) modify(u<<1, l, r, x);
    if (r > mid) modify(u<<1|1, l, r, x);
    push_up(u);
}
node qry(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];
    push_down(u);
    int mid = (tr[u].l + tr[u].r)>>1;
    if (l > mid) return qry(u<<1|1,l,r);
    if (r <= mid) return qry(u << 1, l, r);
    node res{};
    push(res, qry(u<<1, l, r), qry(u<<1|1, l, r));
    return res;
}

int n, q, inv[M];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 2; i <= 300; i++) if (ispr(i)) {
        b[cnt] = i; inv[cnt] = ksm(i,mod-2);
        cnt++;
    }
    rep(i,n) cin >> a[i];
    build(1,1,n);
    while (q--) {
        string op;
        int l, r, x; cin >> op >> l >> r;
        if (op[0] == 'T') {
            int ans = 1;
            auto t = qry(1,l,r);
            ans = t.sum;
            for (int i = 0; i < cnt; i++) if (t.st>>i&1) {
                ans = 1ll*ans*(b[i]-1)%mod;
                ans = 1ll*ans*inv[i]%mod;
            }
            cout << ans << '\n';
        } else {
            cin >> x;
            if (x == 1) continue;
            modify(1,l,r,x);
        }
    }
    return 0;
}