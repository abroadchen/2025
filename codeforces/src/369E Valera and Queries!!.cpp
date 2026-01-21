//
// Created by Psy.C on 2026/1/21.
//
///O((n+m)log(n+m) + (n+m)logM)
#include <iostream>
#include <cstring>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2000005
#define M 1000050
using namespace std;

struct node { int l, r, mark; } seg[N];

int low_bit(const int x) { return x & -x; }
int tr[N];
void add(int x, const int v) {
    for (; x <= M; tr[x] += v, x += low_bit(x)) {}
}
int sum(int x) {//查询前缀和[1, x]
    int ret = 0;
    for (; x > 0; ret += tr[x], x -= low_bit(x)) {}
    return ret;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> seg[i].l >> seg[i].r, seg[i].mark = -1;
    int cnt = n;
    for (int i = 0, tot, dat[N]; i < m; ++i) {
        cin >> tot;//读入分割点
        dat[0] = 0;
        for (int j = 1; j <= tot; ++j) cin >> dat[j];
        dat[tot+1] = M;
        //将区间[dat[p], dat[q]]之间的空隙分割成新区间[l, r]
        for (int p = 0, q = p + 1; q <= tot + 1; ++q, ++p) {
            const int l = dat[p] + 1, r = dat[q] - 1;
            if (l > r) continue;
            seg[cnt++] = {l, r, i};
        }
    }
    sort(seg, seg + cnt, [](const node x, const node y) {
        if (x.l == y.l) {//左端点相同时按右端点升序排列
            if (x.r == y.r) return x.mark < y.mark;//原始区间(-1)优先于查询区间
            return x.r < y.r;
        }
        return x.l > y.l;//按左端点降序排列
    });
    int ans[N] = {};
    memset(tr, 0, sizeof(tr));
    for (int i = 0; i < cnt; ++i) {
        if (seg[i].mark == -1) add(seg[i].r, 1);//原始区间：在右端点处加1
        else ans[seg[i].mark] += sum(seg[i].r);//查询区间：统计覆盖的原始区间数
    }
    //每个查询的原始区间总数减去相交区间数，即不相交的区间数量
    for (int i = 0; i < m; ++i) cout << n - ans[i] << '\n';
    return 0;
}