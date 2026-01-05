//
// Created by Psy.C on 2026/1/5.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200000
#define mod 1000000000
using namespace std;

int add(int x, const int y) {
    x += y, x -= x >= mod ? mod : 0;
    return x;
}
int add(const int x, const int y, const int z) {
    return add(add(x, y), z);
}

int mul(const int x, const int y) { return static_cast<int>(1ll * x * y % mod); }
int f[N|1];
int fib(const int p) { return p < 0 ? 0 : f[p]; }

struct node {
    int len, sum0, sum1;
    node() = default;
    node(const int l, const int s0, const int s1) : len(l), sum0(s0), sum1(s1) {}
    node operator+(const node &o) const {
        node x(len + o.len, 0, 0);
        x.sum0 = add(sum0, mul(o.sum0, fib(len-2)), mul(o.sum1, fib(len-1)));
        x.sum1 = add(sum1, mul(o.sum0, fib(len-1)), mul(o.sum1, fib(len)));
        return x;
    }
} t[N<<2|2];

#define mid ((l+r)>>1)
void build(const int p, const int l, const int r) {
    if (l == r) {
        cin >> t[p].sum0;
        t[p].len = 1, t[p].sum1 = t[p].sum0;
        return;
    }
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    t[p] = t[p<<1] + t[p<<1|1];//合并节点信息
}

int minus_(int x, const int y) {
    x -= y, x += x < 0 ? mod : 0;
    return x;
}

int s[N|1];
void update(const int p, const int l, const int r, const int x) {
    const int len = r - l + 1;
    t[p].sum0 = add(t[p].sum0, mul(x, s[len - 1]));
    t[p].sum1 = add(t[p].sum1, minus_(mul(x, s[len]), x));
}

int a[N<<2|2];
void pushdown(const int p, const int l, const int r) {
    if (!a[p]) return;
    if (l - r) {
        a[p<<1] = add(a[p<<1], a[p]);
        a[p<<1|1] = add(a[p<<1|1], a[p]);
        update(p<<1, l, mid, a[p]);
        update(p<<1|1, mid+1, r, a[p]);
    }
    a[p] = 0;
}
//将位置x的值修改为y
void change(const int p, const int l, const int r, const int x, const int y) {
    if (l == r) {
        t[p] = node(1, y, y);
        return;
    }
    pushdown(p, l, r);
    if (x <= mid) change(p<<1, l, mid, x, y);
    else change(p<<1|1, mid+1, r, x, y);
    t[p] = t[p<<1] + t[p<<1|1];
}
//返回区间[L,R]的查询结果
node query(const int p, const int l, const int r, const int L, const int R) {
    if (l == L && r == R) return t[p];
    pushdown(p, l, r);
    if (R <= mid) return query(p<<1, l, mid, L, R);
    if (L > mid) return query(p<<1|1, mid+1, r, L, R);
    return query(p<<1, l, mid, L, mid) + query(p<<1|1, mid+1, r, mid+1, R);
}
//对区间[L,R]内的每个位置加上x
void modify(const int p, const int l, const int r, const int L, const int R, const int x) {
    if (l == L && r == R) {
        a[p] = add(a[p], x);
        update(p, l, r, x);
        return;
    }
    pushdown(p, l, r);
    if (R <= mid) modify(p<<1, l, mid, L, R, x);
    else if (L > mid) modify(p<<1|1, mid+1, r, L, R, x);
    else modify(p<<1, l, mid, L, mid, x), modify(p<<1|1, mid+1, r, mid+1, R, x);
    t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
    fast;
    f[0] = f[1] = 1;
    for (int i = 2; i <= N; ++i) f[i] = add(f[i-1], f[i-2]);
    s[0] = 1;
    for (int i = 1; i <= N; ++i) s[i] = add(s[i-1], f[i]);
    int n, m; cin >> n >> m;
    build(1, 1, n);
    for (int i = 1, op, x, y, z; i <= m; ++i) {
        cin >> op >> x >> y;
        switch (op) {
            case 1://单点修改
                change(1, 1, n, x, y);
                break;
            case 2:
                cout << query(1, 1, n, x, y).sum0 << '\n';
                break;
            case 3:
                cin >> z;
                modify(1, 1, n, x, y, z);
            default: ;
        }
    }
    return 0;
}