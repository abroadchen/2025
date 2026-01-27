//
// Created by Psy.C on 2026/1/26.
//
/**
* l, r;: 区间左右边界
ld mul: 区间乘积
ld ls: 左侧累积值
ld rs: 右侧累积值
 */
#include <iostream>
#include <algorithm>
#include <iomanip>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define ii pair<int, int>
#define N 300005
using namespace std;

struct node {
    int l, r;
    ld mul, ls, rs;
} tr[N<<2];

void push_up(node &p, const node &ls, const node &rs) {
    p.mul = ls.mul * rs.mul;//合并乘积
    p.ls = (ls.ls + ls.mul * rs.ls);//合并左侧累积值
    p.rs = (rs.rs + rs.mul * ls.rs);
}

void build(const int p, const int ln, const int rn) {
    tr[p] = {ln, rn, 1, 1, 1};//初始化节点
    if (ln == rn) return;
    const int mid = (ln + rn) >> 1;
    build(p<<1, ln, mid); build(p<<1|1, mid+1, rn);
    push_up(tr[p], tr[p<<1], tr[p<<1|1]);
}

void update(const int p, const int x) {
    if (tr[p].l == x && tr[p].r == x) {//叶子节点更新
        tr[p].mul = tr[p].mul / 2.;
        tr[p].ls = tr[p].mul;
        tr[p].rs = tr[p].mul;
        return;
    }
    if (const int mid = (tr[p].l + tr[p].r) >> 1; x <= mid) update(p<<1, x);
    else update(p<<1|1, x);
    push_up(tr[p], tr[p<<1], tr[p<<1|1]);
}

node query(const int p, const int ln, const int rn) {
    if (ln <= tr[p].l && tr[p].r <= rn) return tr[p];
    const int mid = (tr[p].l + tr[p].r) >> 1;
    if (rn <= mid) return query(p<<1, ln, rn);//区间完全在左半部分
    if (ln >= mid + 1) return query(p<<1|1, ln, rn);
    node t{};
    push_up(t, query(p<<1, ln, rn), query(p<<1|1, ln, rn));
    return t;
}

int n;
ld get(const ld p) {
    const auto x = query(1, static_cast<int>(p), n);//查询右侧部分
    const ld r = x.ls;//获取右侧累积值
    const auto y = query(1, 1, static_cast<int>(p));
    const ld l = y.rs;
    return l * r;
}

int main() {
    fast;
    cin >> n;
    ld a[N], ans = 0; ii b[N];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; b[i] = {a[i], i};//值-位置对
    }
    sort(b + 1, b + n + 1, [](const ii& x, const ii& y) {
        return x > y;
    });
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        ans += get(b[i].second) / 2.*b[i].first;//累加贡献
        update(1, b[i].second);
    }
    //输出平均值
    cout << fixed << setprecision(15) << ans / (static_cast<ld>(n)*static_cast<ld>(n));
    return 0;
}