//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
a[i] 表示第 i 个区间 [l, r]，带属性 p。
tr 是主席树（可持久化权值线段树），每个节点存 mn（最小值）。N*21 ≈ 3e5 * 21，是典型的主席树空间
按左端点 l 从大到小降序排序
主席树版本化建树：新版本 x 从旧版本 y 复制而来，只在叶节点 p 处做修改（取 min），然后自底向上取最大值作为节点 mn
在某个版本 x 里查询位置区间 [L, R] 上的 mn 的最大值（取 ans）
因为按 l 降序排好，rt[res] 这个版本汇聚了所有 l >= x 的区间。对每个查询 (l,r,x,y)：

用二分找到满足 a[l].l >= x 的最大下标 res（即收集"左端点 ≥ x"的所有区间）。
在主席树版本 rt[res] 里查询位置范围 [l, r] 上的信息，得到 ans。
若 ans <= y 输出 yes，否则 no，并 fflush。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i = 1; i <= (n); ++i)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 3e5+10, inf = 0x3f3f3f3f;

struct ln {
    int l, r, p;
    friend bool operator<(const ln &a, const ln &b) {
        return a.l > b.l;
    }
} a[N];

struct pst { int l, r, mn; } tr[N*21];

int cnt;
void upd(int &x, int y, int l, int r, int p, int t) {
    x = ++cnt; tr[x] = tr[y];
    if (l == r) { tr[x].mn = min(tr[x].mn, t); return; }
    if (p <= mid) upd(tr[x].l, tr[y].l, l, mid, p, t);
    else upd(tr[x].r, tr[y].r, mid+1, r, p, t);
    tr[x].mn = max(tr[tr[x].l].mn, tr[tr[x].r].mn);
}

int ans;
void qry(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) { ans = max(ans, tr[x].mn); return; }
    if (L <= mid) qry(tr[x].l, l, mid, L, R);
    if (R > mid) qry(tr[x].r, mid+1, r, L, R);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int rt[N];
int main() {
    int n, m, k; tr[0].mn = inf; scanf("%d%d%d",&n,&m,&k);
    rep(i,k) a[i].l = rd(), a[i].r = rd(), a[i].p = rd();
    sort(a+1, a+k+1);
    rep(i,k) upd(rt[i], rt[i-1], 1, n, a[i].p, a[i].r);
    int l, r, x, y;
    while (m--) {
        l = rd(), r = rd(), x = rd(), y = rd();
        int lx = 1, rx = k, res = 0;
        while (lx <= rx) {
            int md = (lx+rx)>>1;
            if (a[md].l >= x) res = md, lx = md+1; else rx = md-1;
        }
        bool f = 0;
        if (res) {
            ans = 0; qry(rt[res], 1, n, l, r);
            if (ans <= y) f = 1;
        }
        if (f) puts("yes"); else puts("no");
        fflush(stdout);
    }
    return 0;
}