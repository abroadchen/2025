//
// Created by Psy.C on 2026/4/13.
//
/**
最小值(mn)、最大值(mx)、懒惰标记(laz)、区间和(sum)

对节点rt打标记，区间[L,R]全部赋值为val
更新最小值、最大值、懒惰标记为val
更新区间和
更新父节点的sum、mn、mx为左右儿子的合并结果
如果有懒惰标记，向下传递给左右儿子
区间[l,r]中所有小于val的值更新为val
如果区间最小值≥val，直接返回
如果区间最大值≤val，整个区间更新为val
否则递归更新左右子区间

d[i]存储i的所有因数
l[i][0], l[i][1]: 因数i的第1、2次出现位置
r[i][0], r[i][1]: 因数i的最新、次新出现位置
val[i]: 值i对应的贡献

初始化线段树，位置i初始值为i
从大到小处理每个因数i
根据因数出现位置更新线段树
计算val[i]
通过差分的方式计算每个因数的贡献

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, M = 8e5+5;

struct sgt {
    struct node { int mn, mx, laz; ll sum; } t[M];
    void tag(int rt, int L, int R, int val) {
        t[rt].mn = t[rt].mx = t[rt].laz = val;
        t[rt].sum = 1ll*(R - L + 1)*t[rt].mn;
    }
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
    void push_up(int rt) {
        t[rt].sum = t[ls(rt)].sum + t[rs(rt)].sum;
        t[rt].mn = min(t[ls(rt)].mn, t[rs(rt)].mn);
        t[rt].mx = max(t[ls(rt)].mx, t[rs(rt)].mx);
    }
    void pushdown(int rt, int L, int R) {
        if (!t[rt].laz) return;
        int mid = (L+R)>>1;
        tag(ls(rt), L, mid, t[rt].laz), tag(rs(rt), mid+1, R, t[rt].laz);
        t[rt].laz = 0;
    }
    void update(int rt, int L, int R, int l, int r, int val) {
        if (l > r || t[rt].mn >= val) return;
        if (L >= l && R <= r && t[rt].mx <= val)
            return tag(rt, L, R, val);
        pushdown(rt, L, R);
        int mid = (L+R)>>1;
        if (l <= mid) update(ls(rt), L, mid, l, r, val);
        if (r > mid) update(rs(rt), mid+1, R, l, r, val);
        push_up(rt);
    }
} T;

vector<int> d[N];
void init() {
    for (int i = 1; i <= N-5; ++i)
        for (int j = i; j <= N-5; j += i)
            d[j].push_back(i);
}

int n, a[N], l[N][2], r[N][2];
ll val[N];
int main() {
    fast; init();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        for (auto j : d[a[i]]) {
            if (!l[j][0]) l[j][0] = i;
            else if (!l[j][1]) l[j][1] = i;
            r[j][1] = r[j][0], r[j][0] = i;
        }
    }
    for (int i = 1; i <= n; ++i) T.update(1, 1, n, i, i, i);
    for (int i = N-4; i; --i) {
        if (l[i][0] != r[i][0]) {
            T.update(1, 1, n, 1, l[i][0], r[i][1]);
            T.update(1, 1, n, l[i][0]+1, l[i][1], r[i][0]);
            T.update(1, 1, n, l[i][1]+1, n, n+1);
        }
        val[i] = 1ll*n*(n+1) - T.t[1].sum;
    }
    ll ans = 0;
    for (int i = 1; i <= N-5; ++i)
        ans += (val[i+1] - val[i])*i;
    cout << ans << '\n';
    return 0;
}