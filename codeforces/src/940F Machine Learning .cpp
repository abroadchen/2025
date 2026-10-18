//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+5;

int block;
struct qu {
    int l, r, t, id;
    friend bool operator<(const qu& a, const qu& b) {
        return a.l/block^b.l/block ? a.l < b.l : a.r/block^b.r/block ? a.r < b.r : a.t < b.t;
    }
} q[N];
struct node { int pos, val; } c[N];

int num[N], cnt[N];
void add(int pos) { --num[cnt[pos]]; num[++cnt[pos]]++; }
void del(int pos) { --num[cnt[pos]]; num[--cnt[pos]]++; }


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], cq, cc, ans[N];
vector<int> v;
int main() {
    int n = rd(), m = rd(); block = pow(n, 2.0/3.0);
    for (int i = 1; i <= n; i++) {
        a[i] = rd(); v.push_back(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int op = rd();
        if (op&1) {
            q[++cq].l = rd(); q[cq].r = rd();
            q[cq].t = cc; q[cq].id = cq;
        } else {
            c[++cc].pos = rd(); c[cc].val = rd();
            v.push_back(c[cc].val);
        }
    }
    sort(q+1, q+cq+1); ranges::sort(v);
    v.erase(ranges::unique(v).begin(), v.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    for (int i = 1; i <= cc; i++)
        c[i].val = lower_bound(v.begin(), v.end(), c[i].val) - v.begin();
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= cq; i++) {
        int L = q[i].l, R = q[i].r;
        while (l < L) del(a[l++]);
        while (l > L) add(a[--l]);
        while (r < R) add(a[++r]);
        while (r > R) del(a[r--]);
        while (t < q[i].t) {
            t++;
            if (L <= c[t].pos && R >= c[t].pos) { del(a[c[t].pos]); add(c[t].val); }
            swap(a[c[t].pos], c[t].val);
        }
        while (t > q[i].t) {
            if (L <= c[t].pos && R >= c[t].pos) { del(a[c[t].pos]); add(c[t].val); }
            swap(a[c[t].pos], c[t].val);
            t--;
        }
        for (ans[q[i].id] = 1; num[ans[q[i].id]]; ans[q[i].id]++) {}
    }
    for (int i = 1; i <= cq; i++) printf("%d\n", ans[i]);
    return 0;
}