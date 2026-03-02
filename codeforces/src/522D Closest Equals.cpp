//
// Created by Psy.C on 2026/3/1.
//
/**
n, m：数组长度和查询数量
a[N]：输入数组
pre[N]：记录每个位置上次相同元素的位置
rep[N]：记录每个位置下次相同元素的位置
res[N]：存储查询结果

pre数组：pre[i]记录位置i上次出现相同元素的位置
rep数组：rep[mp[a[i]]] = i记录上次相同元素的下一个位置
mp映射：维护每个值最后出现的位置

如果当前位置有前驱相同元素，更新当前位置的距离值
滑动窗口：随着查询左端点的移动，移除过期元素的影响
移除影响：将rep[x]位置的值更新为mod（相当于移除）
区间查询：查询[1, q[i].r]范围内的最小距离
如果结果是mod，说明没有重复元素，输出-1；否则输出实际距离
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lrt int l, int r, int rt
using namespace std;
constexpr int N = 5e5+1, mod = 1e9+7;

int st[N<<2];//区间最小值
void push_up(lrt) {//父节点为左右子节点的最小值
    st[rt] = min(st[rt<<1], st[rt<<1|1]);
}
void build(lrt) {
    if (l == r) { st[rt] = mod; return; }
    const int mid = (l + r) >> 1;
    build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
    push_up(l, r, rt);
}
void update(lrt, const int pos, const int d) {
    if (l == r) { st[rt] = d; return; }
    const int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, rt<<1, pos, d);
    if (mid < pos) update(mid+1, r, rt<<1|1, pos, d);
    push_up(l, r, rt);//回溯时更新父节点
}
int query(lrt, const int L, const int R) {
    if (L <= l && r <= R) return st[rt];
    const int mid = (l + r) >> 1;
    int ans = mod;
    if (L <= mid) ans = min(ans, query(l, mid, rt<<1, L, R));
    if (mid < R) ans = min(ans, query(mid+1, r, rt<<1|1, L, R));
    return ans;
}

int n, m, a[N], pre[N], rep[N], res[N];
struct node {
    int l, r, id;
    bool operator<(const node& o) const {
        if (l == o.l) return r < o.r;
        return l < o.l;
    }
} q[N];
map<int, int> mp;

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q, q+m);
    for (int i = 1; i <= n; ++i) {
        pre[i] = mp[a[i]];
        if (mp[a[i]]) rep[mp[a[i]]] = i;
        mp[a[i]] = i;
    }
    build(1, n, 1);
    for (int i = 1; i <= n; ++i)
        if (pre[i]) update(1, n, 1, i, i-pre[i]);
    int x = 1;
    for (int i = 0; i < m; ++i) {
        while (x < q[i].l) {
            if (rep[x]) update(1, n, 1, rep[x], mod);
            x++;
        }
        res[q[i].id] = query(1, n, 1, 1, q[i].r);
    }
    for (int i = 0; i < m; ++i)
        cout << (res[i] == mod ? -1 : res[i]) << '\n';
    return 0;
}