//
// Created by Psy.C on 2026/2/8.
//
/**
sum[N<<2]: 区间和，存储每个节点区间的值
col[N<<2]: 染色标记，表示该区间是否被统一染色
laz[N<<2]: 懒惰标记数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

ll sum[N<<2], col[N<<2];
void push_up(const int rt) {
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    //如果左右子树颜色相同，则父节点颜色也相同，否则为0（表示不同色）
    col[rt] = col[rt<<1] == col[rt<<1|1] ? col[rt<<1] : 0;
}

//区间[l,r]，节点编号rt
void build(const int l, const int r, const int rt) {
    if (l == r) { col[rt] = l; return; }
    const int mid = (l + r) >> 1;
    build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
    push_up(rt);
}

ll laz[N<<2];
void pushdown(const int rt, const int len) {
    if (col[rt]) {//当前节点被染色
        col[rt<<1] = col[rt<<1|1] = col[rt];//将颜色传递给左右子节点
        //len-(len>>1)和len>>1: 分别计算左右子区间的长度
        sum[rt<<1] += laz[rt]*(ll)(len-(len>>1));
        sum[rt<<1|1] += laz[rt]*(ll)(len>>1);
        laz[rt<<1] += laz[rt];
        laz[rt<<1|1] += laz[rt];
        col[rt] = laz[rt] = 0;//清空当前节点的标记
    }
}

//将[L,R]区间更新为val
void update(const int l, const int r, const int rt, const int L, const int R, const ll val) {
    if (L <= l && r <= R && col[rt]) {//当前区间完全在更新范围内且已被染色
        //颜色变化的差值 区间长度
        sum[rt] += abs(col[rt] - val) * (ll)(r - l + 1);
        laz[rt] += abs(col[rt] - val);
        col[rt] = val;
        return;
    }
    pushdown(rt, r - l + 1);
    const int mid = (l + r) >> 1;
    if (L <= mid) update(l, mid, rt<<1, L, R, val);
    if (R > mid) update(mid+1, r, rt<<1|1, L, R, val);
    push_up(rt);//更新父节点
}

//查询[L,R]区间的sum值
ll query(const int l, const int r, const int rt, const int L, const int R) {
    if (L <= l && r <= R) return sum[rt];
    pushdown(rt, r - l + 1);
    ll ans = 0;
    const int mid = (l + r) >> 1;
    if (L <= mid) ans += query(l, mid, rt<<1, L, R);
    if (R > mid) ans += query(mid+1, r, rt<<1|1, L, R);
    return ans;
}


int main() {
    fast;
    int n, m, op, l, r; cin >> n >> m; build(1, n, 1);
    ll x;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            update(1, n, 1, l, r, x);
        } else {
            cin >> l >> r;
            cout << query(1, n, 1, l, r) << '\n';
        }
    }
    return 0;
}