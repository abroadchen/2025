//
// Created by Psy.C on 2025/12/21.
//
/*
*w[i][j]: 存储i^j的值
num[i][j]: 存储从0到i的j次幂之和 0^j + 1^j + 2^j + ... + i^j
*l, r: 区间左右端点
laz: 懒标记(-1表示无标记)
sum[6]: 存储区间内各种次幂的和
 *
 *向上传递：合并左右子树的信息
*构建线段树：
叶子节点：sum[i] = l^i * a[l]
非叶子节点：递归构建并向上合并
*更新节点：将区间[l,r]全部设为val
sum[i] = val * (l^i + (l+1)^i + ... + r^i)
 *下传懒标记
 *区间更新：将[l,r]设为val
 *区间查询：查询[l,r]区间内k次幂的和
 *
 * ∑(i=l to r) (i-k)^x，使用二项式展开： (i-k)^x = ∑(j=0 to x) C(x,j) * i^j * (-k)^(x-j)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
#define M (N+10)
#define mod 1000000007
#define mid ((tr[p].l+tr[p].r)>>1)
#define ls p<<1
#define rs (ls|1)
using namespace std;

ll w[M][6], num[M][6];
void init() {
    memset(num, 0, sizeof(num));
    memset(w, 0, sizeof(w));
    for (ll i = 0; i <= N; ++i) for (int j = 0; j < 6; ++j) {
        int k = j; ll t = 1;
        while (k--) t = (t * i) % mod;//i^j
        w[i][j] = t;
        if (i != 0) num[i][j] = (num[i-1][j] + t) % mod;//0^j + 1^j + ... + (i-1)^j + i^j
    }
}

struct node { int l, r, laz; ll sum[6]; } tr[M<<2];

void push_up(const int p) {
    for (int i = 0; i < 6; ++i) tr[p].sum[i] = (tr[ls].sum[i] + tr[rs].sum[i]) % mod;
}


ll a[M];
void build(const int p, const int l, const int r) {
    tr[p].l = l; tr[p].r = r; tr[p].laz = -1;
    if (l == r) {
        for (int i = 0; i < 6; ++i) tr[p].sum[i] = (w[l][i] * a[l]) % mod;
        return;
    }
    build(ls, l, mid); build(rs, mid+1, r);
    push_up(p);
}

void update(const int p, const int val) {
    tr[p].laz = val;
    const int l = tr[p].l, r = tr[p].r;
    for (int i = 0; i < 6; ++i) tr[p].sum[i] = ((val * (num[r][i]-num[l-1][i]))%mod+mod)%mod;
}

void push_down(const int p) {
    if (tr[p].laz != -1) {
        update(ls, tr[p].laz);
        update(rs, tr[p].laz);
        tr[p].laz = -1;
    }
}

void add(const int p, const int l, const int r, const int val) {
    if (tr[p].l == l && tr[p].r == r) { update(p, val); return; }
    push_down(p);
    if (l > mid) add(rs, l, r, val);
    else if (r <= mid) add(ls, l, r, val);
    else {
        add(ls, l, mid, val);
        add(rs, mid+1, r, val);
    }
    push_up(p);
}

ll query(const int p, const int l, const int r, const int k) {
    if (tr[p].l == l && tr[p].r == r) return tr[p].sum[k];
    push_down(p);
    if (l > mid) return query(rs, l, r, k);
    if (r <= mid) return query(ls, l, r, k);
    return (query(ls, l, mid, k) + query(rs, mid+1, r, k)) % mod;
}

int l, r;
ll g(const int a1, const int b, const int c) {//计算差分公式中的各项
    return (query(1, l, r, c) * ((a1 * w[l-1][b])%mod))%mod;
}

int main() {
    fast;
    init();
    int n, q, x; cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    char str[2];
    while (q--) {
        cin >> str >> l >> r >> x;
        if (str[0] == '=') add(1, l, r, x);
        else {
            ll t = 0;
            if (x == 0) t = query(1, l, r, 0);
            else if (x == 1) t = ((g(1,0,1)-g(1,1,0))%mod+mod)%mod;
            else if (x == 2) t = ((g(1,0,2)-g(2,1,1)+g(1,2,0))%mod+mod)%mod;
            else if (x == 3) t = ((g(1,0,3)-g(3,1,2)+
                g(3,2,1)-g(1,3,0))%mod+mod)%mod;
            else if (x == 4) t = ((g(1,0,4)-g(4,1,3)+
                g(6,2,2)-g(4,3,1)+g(1,4,0))%mod+mod)%mod;
            else if (x == 5) t = ((g(1,0,5)-g(5,1,4)+
                g(10,2,3)-g(10,3,2)+g(5,4,1)-g(1,5,0))%mod+mod)%mod;
            cout << t << '\n';
        }
    }
    return 0;
}