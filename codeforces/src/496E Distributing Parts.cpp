//
// Created by Psy.C on 2026/2/21.
//
/**
type: 0表示区间，1表示查询
l, r: 区间的左右端点
k: 查询的容量（能容纳的区间数量）
id: 原始编号

前n个是区间，后m个是查询
type=0: 区间 [l,r]
type=1: 查询 [l,r,k]（容量为k）

按左端点升序
左端点相同时按右端点降序
左右端点都相同时，查询优先于区间（type=1优先于type=0）

按左端点排序：扫描线从左到右
右端点降序：优先处理包含更多区间的查询
查询优先：确保在处理区间前，可用的查询已在数据结构中

找到右端点≥当前区间右端点的最小查询
这样确保区间被查询完全包含（查询.l ≤ 区间.l ≤ 区间.r ≤ 查询.r）

排序：O((n+m)log(n+m))
扫描过程：O((n+m)log m)
总体：O((n+m)log(n+m))

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1;

struct node { bool type; int l, r, k, id; } a[N<<1];
int n, m;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        a[i].type = 0;
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    cin >> m;
    rep(i,m) {
        a[i+n].type = 1;
        cin >> a[i+n].l >> a[i+n].r >> a[i+n].k;
        a[i+n].id = i;
    }
    sort(a + 1, a + n + m + 1, [](const node& x, const node& y) {
        if (x.l != y.l) return x.l < y.l;
        if (x.r != y.r) return x.r > y.r;
        return x.type > y.type;
    });
    vector ans(n+1, 0);
    set<ii> st;
    rep(i,n+m) {
        if (a[i].type == 1) st.insert({a[i].r, i});
        else {
            auto it = st.lower_bound({a[i].r, -1});//相同右端点的第一个元素
            if (it == st.end()) { cout << "NO\n"; return 0; }
            const int pos = it->second;
            ans[a[i].id] = a[pos].id;
            a[pos].k--;//使用容量
            if (!a[pos].k) st.erase(it);//容量用完删除
        }
    }
    cout << "YES\n";
    rep(i,n) cout << ans[i] << ' ';
    return 0;
}