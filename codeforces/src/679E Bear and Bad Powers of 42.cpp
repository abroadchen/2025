//
// Created by Psy.C on 2026/4/14.
//
///时间复杂度：O(n log n + q log n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 5e5+5, inf = 1e18;

int v[15];
int get(int x) {//x在v数组中的位置
    return lower_bound(v + 1, v + 11, x) - v;
}

struct sgt {
#define ls (p<<1)
#define rs (p<<1|1)
    ///左右边界、最小值、覆盖值、ID、懒惰标记
    struct node { int l, r, mn, cov, id, add; } t[N<<2];
    ///更新父节点的最小值
    void push_up(int p) {
        t[p].mn = min(t[ls].mn, t[rs].mn);
    }
    ///对节点p进行覆盖操作
    void docov(int p, int pos, int id) {
        t[p].mn = t[p].cov = pos;
        t[p].id = id;
        t[p].add = 0;
    }
    ///加法操作：减少当前值，必要时更新ID
    void do_add(int p, int k) {
        if (!t[p].id) {
            t[p].mn -= k;
            t[p].add += k;
            return;
        }
        t[p].cov -= k;
        while (t[p].cov < 0) {
            if (t[p].id + 1 > 10) {
                t[p].cov = 0;
                break;
            }
            t[p].cov += v[t[p].id + 1] - v[t[p].id];
            t[p].id++;
        }
        t[p].mn = t[p].cov;
    }
    ///下传标记到左右子树
    void pushdown(int p) {
        if (t[p].id) {
            docov(ls, t[p].cov, t[p].id);
            docov(rs, t[p].cov, t[p].id);
            t[p].cov = t[p].id = 0;
        }
        if (t[p].add) {
            do_add(ls, t[p].add);
            do_add(rs, t[p].add);
            t[p].add = 0;
        }
    }
    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        t[p].mn = t[p].cov = t[p].id = t[p].add = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(p);
    }
    ///区间覆盖操作
    void cover(int p, int L, int R, int pos, int id) {
        if (t[p].r < L || t[p].l > R) return;
        if (t[p].l >= L && t[p].r <= R) {
            docov(p, pos, id);
            return;
        }
        pushdown(p);
        cover(ls, L, R, pos, id); cover(rs, L, R, pos, id);
        push_up(p);
    }
    ///区间加法操作
    void add(int p, int L, int R, int k) {
        if (t[p].r < L || t[p].l > R) return;
        if (t[p].l >= L && t[p].r <= R && (t[p].mn >= k || t[p].id)) {
            do_add(p, k);
            return;
        }
        pushdown(p);
        add(ls, L, R, k); add(rs, L, R, k);
        push_up(p);
    }
    ///单点查询操作
    int query(int p, int pos) {
        if (t[p].l == t[p].r) return v[t[p].id] - t[p].mn;
        pushdown(p);
        int mid = (t[p].l + t[p].r)>>1;
        if (mid >= pos) return query(ls, pos);
        return query(rs, pos);
    }
    ///区间最小值查询
    int dfs(int p, int L, int R) {
        if (t[p].r < L || t[p].l > R) return inf;
        if (t[p].l >= L && t[p].r <= R) return t[p].mn;
        pushdown(p);
        return min(dfs(ls, L, R), dfs(rs, L, R));
    }
} sg;

///v[i] = 42^i
void init() {
    v[0] = 1;
    for (int i = 1; i <= 10; ++i) v[i] = v[i-1]*42;
}

int n, q, a[N];
signed main() {
    fast; init();
    cin >> n >> q; sg.build(1, 1, n);
    for (int i = 1; i <= n; ++i) {//对每个位置i，根据a[i]设置初始状态
        cin >> a[i];
        int idx = get(a[i]);
        sg.cover(1, i, i, v[idx] - a[i], idx);
    }
    while (q--) {
        int op, x, y, z; cin >> op >> x;
        //查询位置x的值
        if (op == 1) cout << sg.query(1, x) << '\n';
        else if (op == 2) {//将区间[x,y]覆盖为z
            cin >> y >> z;
            int idx = get(z);
            sg.cover(1, x, y, v[idx]-z, idx);
        } else if (op == 3) {//在区间[x,y]上不断减z，直到区间内所有值≤0
            cin >> y >> z;
            do {
                sg.add(1, x, y, z);
            } while (sg.dfs(1, x, y) <= 0);
        }
    }
    return 0;
}