//
// Created by Psy.C on 2026/3/6.
//
/**
mx[i]：第i个节点存储的最大值
ls[i]：第i个节点的左子节点索引
rs[i]：第i个节点的右子节点索引
tag[i]：第i个节点的懒惰标记（用于懒惰传播）
n：区间数量
m：可能是最小间隔参数
R：最大右端点
rt：线段树根节点
q：优先队列，存储待处理的事件

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 12e6;
struct node {
    int l, r;
    bool operator<(const node& o) const {
        return r > o.r || (r == o.r && l > o.l);
    }
};

int mx[N], ls[N], rs[N], tag[N];
inline void push_up(int x) {
    mx[x] = max(mx[ls[x]], mx[rs[x]]) + tag[x];
}
int tot;
void update(int& rt, int l, int r, int L, int R, int x) {
    if (!rt) rt = ++tot;//如果节点不存在，创建新节点
    if (L <= l && r <= R) {
        mx[rt] += x; tag[rt] += x;
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) update(ls[rt], l, mid, L, R, x);
    if (R > mid) update(rs[rt], mid + 1, r, L, R, x);
    push_up(rt);
}

void modify(int& rt, int l, int r, int x, int y) {
    if (!rt) rt = ++tot;
    if (l == r) { mx[rt] = y; return; }
    int mid = (l + r) >> 1;
    x <= mid ? modify(ls[rt], l, mid, x, y) : modify(rs[rt], mid + 1, r, x, y);
    push_up(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (!rt || L > R) return 0;
    if (L <= l && r <= R) return mx[rt];
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res = max(res, query(ls[rt], l, mid, L, R));
    if (R > mid) res = max(res, query(rs[rt], mid + 1, r, L, R));
    res += tag[rt];
    return res;
}

int n, m, R, rt;
priority_queue<node> q;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, l, r; i <= n; ++i) {
        cin >> l >> r;
        if (r < 0) continue;
        l = max(0, l);//左端点不能为负
        q.emplace(l, r); q.emplace(-1, l);//将区间事件和起始事件加入队列
        R = max(R, r);
    }
    int lst = -1;//上一个处理的位置
    while (!q.empty()) {
        int l = q.top().l, r = q.top().r; q.pop();
        if (l >= 0) {//如果是区间事件
            update(rt, 0, R, l, r, 1);//在线段树中更新区间[l,r]，增加1
            continue;
        }
        if (r == lst) continue;
        int x = lst >= 0 ? query(rt, 0, R, lst, lst) : 0,
            y = query(rt, 0, R, 0, r-m);// 查询[0, r-m]区间的最大值
        if (l == -1 || y > x) {
            lst = r;//更新lst为当前位置
            modify(rt, 0, R, r, y);//修改位置r的值为y
            if (r + m <= R) q.emplace(-2, r + m);//添加新的事件
        }
    }
    cout << mx[rt] << '\n';
    return 0;
}