//
// Created by Psy.C on 2026/4/14.
//
/**
x, y: 参数（斜率k和查询时刻）
l, r: 时间区间
id: 标识符

构建线段树
排序并插入线段
构建时间轴上的凸包
执行查询并输出结果

时间复杂度：O(n log²n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
using namespace std;
constexpr int N = 3e5+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct node {
    ll x, y; int id;
    bool operator<(const node &o) const {
        return x != o.x ? x < o.x : y > o.y;
    }///按x升序，x相同时按y降序
} q[N];

struct rec {
    ll x, y; int l, r, id;
    bool operator<(const rec &o) const {
        return x != o.x ? x < o.x : y > o.y;
    }
} p[N], w[N];

///计算叉积，用于判断点的相对位置
ll cmp(int u, int v, int y) {
    return (q[u].y-q[v].y)*(q[u].x-q[y].x)-(q[u].y-q[y].y)*(q[u].x-q[v].x);
}
///判断两点是否重合
bool cmp(int u, int v) {
    return q[u].x == q[v].x && q[u].y == q[v].y;
}

struct sgt {
    int l, r, p;///左右边界和指针
#define l(x) tr[x].l
#define r(x) tr[x].r
#define p(x) tr[x].p
} tr[N<<2];

void build(int x, int l, int r) {
    l(x) = l, r(x) = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(x<<1, l, mid), build(x<<1|1, mid+1, r);
}

vector<int> h[N<<2];
void insert(int x, int L, int R, int d) {//将线段d插入区间[L,R]
    int l = l(x), r = r(x);
    if (L <= l && r <= R) { h[x].push_back(d); return; }
    int mid = (l + r) >> 1;
    if (L <= mid) insert(x<<1, L, R, d);
    if (R > mid) insert(x<<1|1, L, R, d);
}

int s[N], t;
///在线段树节点x上维护凸包
///使用单调栈构建上凸壳
void dfs(int x) {
    int l = l(x), r = r(x);
    if (!h[x].empty()) {
        s[t=1] = h[x][0];
        for (int i = 1; i < h[x].size(); ++i) {
            if (cmp(s[t], h[x][i])) continue;
            while (t > 1 && cmp(s[t-1], s[t], h[x][i]) <= 0) t--;
            s[++t] = h[x][i];
        }
        h[x].clear();
        for (int i = 1; i <= t; ++i) h[x].push_back(s[i]);
    }
    if (l == r) return;
    dfs(x<<1), dfs(x<<1|1);
}

///在时间pos查询斜率为k的最大值
///使用凸包上的三分查找
ll query(int x, int pos, ll k) {
    int l = l(x), r = r(x);
    ll res = -inf;
    if (!h[x].empty()) {
        int L = p(x), R = h[x].size()-1;
        while (L < R && (ld)(q[h[x][L]].y-q[h[x][L+1]].y)/(q[h[x][L]].x-q[h[x][L+1]].x) >= -k) L++;
        res = k*q[h[x][L]].x+q[h[x][L]].y;
        p(x) = L;
    }
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (pos <= mid) res = max(res, query(x<<1, pos, k));
    if (pos > mid) res = max(res, query(x<<1|1, pos, k));
    return res;
}

int n, tot, cnt;
ll ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, op; i <= n; ++i) {
        cin >> op;
        if (op == 1) {//添加直线y=ax+b
            ll x, y; cin >> x >> y;
            q[i] = {x, y, ++tot};
            p[tot] = {q[i].x, q[i].y, i, n, i};
        }
        if (op == 2) {//删除直线
            int x; cin >> x;
            p[q[x].id].r = i;
        }
        if (op == 3) {//查询斜率为k的最大值
            ll k; cin >> k;
            w[++cnt] = {k, i, 0, 0, cnt};
        }
    }
    build(1, 1, n);
    sort(p+1, p+tot+1); sort(w+1, w+cnt+1);
    for (int i = 1; i <= tot; ++i) insert(1, p[i].l, p[i].r, p[i].id);
    dfs(1);
    for (int i = 1; i <= cnt; ++i) ans[w[i].id] = query(1, w[i].y, w[i].x);
    for (int i = 1; i <= cnt; ++i) {
        if (ans[i] == -inf) cout << "EMPTY SET\n";
        else cout << ans[i] << '\n';
    }
    return 0;
}