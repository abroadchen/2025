//
// Created by Psy.C on 2026/2/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100505
using namespace std;

//线段树节点，包含左右边界
struct node {
    ll l, r;
    [[nodiscard]] ll mid() const { return (l+r)>>1; }
} tr[N<<2];

//每个区间的最大值 每个区间的值的总和
ll mx[N<<2], sum[N<<2];
void push_up(const ll rt) {//从子节点更新父节点
    mx[rt] = max(mx[rt<<1], mx[rt<<1|1]);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(const ll l, const ll r, const ll rt) {
    tr[rt].l = l, tr[rt].r = r;
    //叶子节点获得输入值
    if (l == r) { cin >> sum[rt]; mx[rt] = sum[rt]; return; }
    const ll mid = tr[rt].mid();
    build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
    push_up(rt);
}

//将位置x的值更新为c
void update(const ll c, const ll l, const ll r, const ll rt, const ll x) {
    if (l == r) { sum[rt] = c; mx[rt] = c; return; }
    if (const ll mid = (l+r)>>1; x <= mid) update(c, l, mid, rt<<1, x);
    else update(c, mid+1, r, rt<<1|1, x);
    push_up(rt);
}

//对范围[l,r]应用取模c操作
void update2(const ll c, const ll l, const ll r, const ll rt) {
    if (tr[rt].l >= l && tr[rt].r <= r) {
        if (mx[rt] < c) return;
        if (tr[rt].l == tr[rt].r) { sum[rt] %= c; mx[rt] %= c; return; }
    }
    if (const ll mid = tr[rt].mid(); r <= mid) update2(c, l, r, rt<<1);
    else if (l > mid) update2(c, l, r, rt<<1|1);
    else {
        update2(c, l, mid, rt<<1);
        update2(c, mid+1, r, rt<<1|1);
    }
    push_up(rt);
}

//范围[l,r]内值的总和
ll query(const ll l, const ll r, const ll rt) {
    if (tr[rt].r == r && tr[rt].l == l) return sum[rt];//完全匹配
    ll res = 0;
    if (const ll mid = tr[rt].mid(); r <= mid) res += query(l, r, rt<<1);
    else if (l > mid) res += query(l, r, rt<<1|1);
    else {
        res += query(l, mid, rt<<1);
        res += query(mid+1, r, rt<<1|1);
    }
    return res;
}

int main() {
    fast;
    ll n, q; cin >> n >> q; build(1, n, 1);
    int op, a, b, c;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b;
            cout << query(a, b, 1) << '\n';
        }
        else if (op == 2) {
            cin >> a >> b >> c;
            update2(c, a, b, 1);
        } else {//点更新
            cin >> a >> b;
            update(b, 1, n, 1, a);
        }
    }
    return 0;
}