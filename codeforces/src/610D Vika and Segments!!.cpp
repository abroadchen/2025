//
// Created by Psy.C on 2026/3/23.
//
/**
l, r：矩形在x轴上的范围
y：扫描线的y坐标
flag：+1表示矩形开始（下边界），-1表示矩形结束（上边界）
l, r：区间范围
tag：懒惰标记，记录该区间被覆盖的矩形数量
sum：该区间实际被覆盖的长度

如果被完全覆盖，返回实际区间长度
如果是叶子节点且未被覆盖，长度为0
否则等于左右子树长度之和

读入矩形坐标，规范化方向
将每个矩形拆分成上下两条扫描线
同时收集所有x坐标用于离散化
按y坐标排序扫描线
对x坐标排序并去重（离散化）

遍历每条扫描线
在线段树中更新对应的x区间
累加面积：当前覆盖长度 × y轴高度差

时间复杂度：
O(n log n)，主要是排序和线段树操作。
空间复杂度：
O(n)，用于存储线段树和离散化坐标
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
struct line {
    int l, r, y, flag;
    bool operator<(const line& o) const {
        return y < o.y;
    }
} ln[N<<2];
struct node { int l, r, tag; ll sum; } tr[N*24];

ll x[N<<2];
void push_up(int u) {
    if (tr[u].tag) tr[u].sum = x[tr[u].r+1] - x[tr[u].l];
    else if (tr[u].l == tr[u].r) tr[u].sum = 0;
    else tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}
void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int mid = (l+r)>>1;
    build(u<<1, l, mid); build(u<<1|1, mid+1, r);
    push_up(u);
}
void update(int u, int l, int r, int v) {
    if (tr[u].l == l && tr[u].r == r) {
        tr[u].tag += v;
        push_up(u);
        return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (r <= mid) update(u<<1, l, r, v);
    else if (l >= mid + 1) update(u<<1|1, l, r, v);
    else {
        update(u<<1, l, mid, v);
        update(u<<1|1, mid+1, r, v);
    }
    push_up(u);
}

int n;
int main() {
    fast;
    cin >> n;
    int cnt = 0;
    for (int i = 0, x1, x2, y1, y2; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 < y2) swap(y1, y2); x1--, y2--; cnt++;
        ln[cnt] = {x1, x2, y1, 1}; x[cnt] = x1; cnt++;
        ln[cnt] = {x1, x2, y2, -1}; x[cnt] = x2;
    }
    sort(ln + 1, ln + cnt + 1);
    sort(x + 1, x + cnt + 1);
    int num = unique(x + 1, x + cnt + 1) - x - 1;
    build(1, 1, cnt-1);
    ll sum = 0;
    for (int i = 1; i <= cnt-1; ++i) {
        int l = lower_bound(x + 1, x + num + 1, ln[i].l) - x,
        r = lower_bound(x + 1, x + num + 1, ln[i].r) - x - 1;
        update(1, l, r, ln[i].flag);
        sum += tr[1].sum*(ln[i+1].y - ln[i].y);
    }
    cout << sum;
    return 0;
}