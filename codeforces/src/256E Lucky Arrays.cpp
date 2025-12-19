//
// Created by Psy.C on 2025/12/18.
//
/*
*l, r: 区间左右端点
lz, rz: 前缀/后缀连续0的长度
ln, rn: 前缀/后缀连续0的第一个/最后一个位置的值
dat: 区间内的有效方案数
*a[i][j]: 表示状态i能否转换到状态j
f[i][j][k]: 长度为i，首为j，尾为k的合法序列方案数
 *
 *每次操作O(log n)，预处理O(n)
 *
*!tr[i<<1].rz：

tr[i<<1].rz 表示左子区间的后缀连续0的长度
!tr[i<<1].rz 为真意味着左子区间最后面没有连续的0
换句话说，左子区间的最右边位置是1
!tr[i<<1|1].lz：

tr[i<<1|1].lz 表示右子区间的前缀连续0的长度
!tr[i<<1|1].lz 为真意味着右子区间最前面没有连续的0
换句话说，右子区间的最左边位置是1
!a[tr[i<<1].rn][tr[i<<1|1].ln]：

tr[i<<1].rn 是左子区间最右侧非0位置的值（应该是1,2,3中的某个）
tr[i<<1|1].ln 是右子区间最左侧非0位置的值（应该是1,2,3中的某个）
a[tr[i<<1].rn][tr[i<<1|1].ln] 表示这两个值是否可以相邻
!a[tr[i<<1].rn][tr[i<<1|1].ln] 为真意味着这两个值不能相邻
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(int i=1; i<=n; ++i)
#define ok(x) (tr[x].lz == tr[x].r - tr[x].l + 1)
using namespace std;

constexpr int N = 8e4+10, M = 10, mod = 777777777;
struct sgt {
    int l, r, lz, rz, ln, rn; ll dat;
} tr[N<<2];

void build(const int i, const int l, const int r) {
    tr[i].l = l; tr[i].r = r;
    tr[i].lz = tr[i].rz = r - l + 1;//初始全为0，所以前缀后缀都是全长
    tr[i].dat = 1;//初始方案数为1
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid + 1, r);
}

int a[M][M];
ll f[N][M][M];
void push_up(const int i) {
    tr[i].lz = tr[i<<1].lz; tr[i].rz = tr[i<<1|1].rz;
    tr[i].ln = tr[i<<1].ln; tr[i].rn = tr[i<<1|1].rn;
    if (ok(i<<1) && ok(i<<1|1)) {//两个子区间都全为0
        tr[i].lz = tr[i].rz = tr[i].r - tr[i].l + 1;
        tr[i].dat = 1;
    }
    if (ok(i<<1) && !ok(i<<1|1)) {//左子区间全为0，右子区间有1
        tr[i].lz += tr[i<<1|1].lz;
        tr[i].ln = tr[i<<1|1].ln;
        tr[i].dat = tr[i<<1|1].dat;
    }
    if (!ok(i<<1) && ok(i<<1|1)) {//左子区间有1，右子区间全为0
        tr[i].rz += tr[i<<1].rz;
        tr[i].rn = tr[i<<1].rn;
        tr[i].dat = tr[i<<1].dat;
    }
    if (!ok(i<<1) && !ok(i<<1|1)) {//两个子区间都有1
        tr[i].dat = tr[i<<1].dat * tr[i<<1|1].dat % mod;
        if (tr[i<<1].rz || tr[i<<1|1].lz) {
            ll t = 0;//中间连接部分的方案数
            rep(j,3) rep(k,3) if (a[tr[i<<1].rn][j] && a[k][tr[i<<1|1].ln]) {
                t = (t + f[tr[i<<1].rz + tr[i<<1|1].lz][j][k]) % mod;
            }
            tr[i].dat = tr[i].dat * t % mod;
        }
    }//相邻元素不允许连接
    if (!tr[i<<1].rz && !tr[i<<1|1].lz && !a[tr[i<<1].rn][tr[i<<1|1].ln]) {
        tr[i].dat = 0;
    }
}

void update(const int i, const int x, const int k) {
    if (tr[i].l == tr[i].r) {
        if (k) tr[i].lz = tr[i].rz = 0;
        else tr[i].lz = tr[i].rz = 1;
        tr[i].ln = tr[i].rn = k;
        return;
    }
    if (tr[i<<1].r >= x) update(i<<1, x, k);
    else update(i<<1|1, x, k);
    push_up(i);//更新完子节点后维护当前节点
}

int n;
ll query() {
    if (tr[1].lz == n) {
        ll t = 0;
        rep(i,3) rep(j,3) t = (t + f[n][i][j]) % mod;
        return t;
    }
    ll ans = tr[1].dat;//基础方案数
    if (tr[1].lz) {//处理前缀部分
        ll t = 0;
        rep(i,3) rep(j,3) if (a[j][tr[1].ln]) {
            t = (t + f[tr[1].lz][i][j]) % mod;
        }
        ans = ans * t % mod;
    }
    if (tr[1].rz) {//处理后缀部分
        ll t = 0;
        rep(i,3) rep(j,3) if (a[tr[1].rn][i]) {
            t = (t + f[tr[1].rz][i][j]) % mod;
        }
        ans = ans * t % mod;
    }
    return ans;
}

int main() {
    fast;
    int m; cin >> n >> m;
    rep(i,3) rep(j,3) cin >> a[i][j];
    f[1][1][1] = f[1][2][2] = f[1][3][3] = 1;
    for (int i = 2; i <= n; ++i) rep(j,3) rep(k,3) rep(l,3) if (a[l][k]) {
        f[i][j][k] = (f[i][j][k] + f[i-1][j][l]) % mod;
    }
    build(1, 1, n);
    rep(i,m) {
        int v; ll t; cin >> v >> t;
        update(1, v, static_cast<int>(t));
        cout << query() << '\n';
    }
    return 0;
}