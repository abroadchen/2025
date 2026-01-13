//
// Created by Psy.C on 2026/1/13.
//
/**
 * g[N]：邻接表存储树结构
 *in[N]：每个节点的进入时间戳（欧拉序起始位置）
 *idx：时间戳计数器
 *p[N]：每个节点的父节点
 *out[N]：每个节点的退出时间戳（欧拉序结束位置）
 *lazy[N<<2]：懒惰标记数组，用于区间更新优化
 *sum[N<<2]：线段树数组，存储区间信息
 *
 *rt：当前节点编号
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500050
using namespace std;


vector<int> g[N];
int in[N], idx, p[N], out[N];
void dfs(const int v, const int pre) {
    in[v] = ++idx;
    for (const auto u : g[v]) {//遍历v的所有邻居
        if (u == pre) continue;
        p[u] = v;//设置u的父节点为v
        dfs(u, v);//递归遍历子节点
    }
    out[v] = idx;
}

int lazy[N<<2], sum[N<<2];
void pushdown(const int rt) {
    if (lazy[rt]) {
        sum[rt<<1] = 1; sum[rt<<1|1] = 1;//更新左右子节点的值
        lazy[rt<<1] = 1; lazy[rt<<1|1] = 1;
        lazy[rt] = 0;
    }
}

void push_up(const int rt) {
    sum[rt] = sum[rt<<1] & sum[rt<<1|1];
}

int query(const int rt, const int l, const int r, const int ql, const int qr) {//查询区间
    if (ql <= l && r <= qr) return sum[rt];
    pushdown(rt);
    const int mid = (l + r) >> 1;
    int ret = 1;
    if (ql <= mid) ret &= query(rt<<1, l, mid, ql, qr);
    if (qr > mid) ret &= query(rt<<1|1, mid+1, r, ql, qr);
    return ret;
}
//将区间[ql, qr]内的所有位置标记为1
void fill(const int rt, const int l, const int r, const int ql, const int qr) {
    if (ql <= l && r <= qr) { sum[rt] = 1; lazy[rt] = 1; return; }
    pushdown(rt);
    const int mid = (l + r) >> 1;
    if (ql <= mid) fill(rt<<1, l, mid, ql, qr);
    if (qr > mid) fill(rt<<1|1, mid+1, r, ql, qr);
    push_up(rt);
}
//将单点pos的值设置为0
void empty(const int rt, const int l, const int r, const int pos) {
    if (l == r) { sum[rt] = 0; return; }
    pushdown(rt);
    if (const int mid = (l + r) >> 1; pos <= mid) empty(rt<<1, l, mid, pos); else {
        empty(rt<<1|1, mid+1, r, pos);
    }
    push_up(rt);
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    p[1] = 0;//根节点的父节点为0
    dfs(1, 0);
    int q; cin >> q;
    while (q--) {
        int op, x; cin >> op >> x;
        if (op == 1) {
            //如果x的子树未完全填充
            if (!query(1, 1, n, in[x], out[x])) empty(1, 1, n, in[p[x]]);//清空父节点
            fill(1, 1, n, in[x], out[x]);//填充x的子树
        } else if (op == 2) empty(1, 1, n, in[x]); else {//清空节点x
            cout << query(1, 1, n, in[x], out[x]) << '\n';//查询节点x的子树是否完全填充
        }
    }
    return 0;
}