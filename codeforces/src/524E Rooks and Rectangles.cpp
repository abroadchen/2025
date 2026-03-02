//
// Created by Psy.C on 2026/3/2.
//
/**
扫描线算法：按x坐标顺序处理点和查询
动态添加点：将x坐标≤查询右边界的所有点加入线段树
更新线段树：在y位置存储对应的x值
查询判断：查询[y1,y2]范围内最小的x值，如果≥x1则存在满足条件的点

交换维度：交换n和m
交换坐标：将所有点的x、y坐标互换
重新排序：按新的坐标重新排序
交换查询边界：交换查询矩形的x、y边界

读取参数：网格大小(n,m)，点数k，查询数q
读取点坐标：读取k个点的坐标
排序点：按x坐标排序
读取查询：读取查询矩形信息
排序查询：按右边界x2排序
第一次处理：在原始坐标系下处理
坐标变换：调用solve函数交换坐标轴
第二次处理：在交换后的坐标系下处理

时间复杂度：O((k+q)log(k+q)logm)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1, M = 1e5+1, inf = 0x3f3f3f3f;
struct node { int val; } tr[M<<2];///每个节点存储最小值

///u-节点编号，l,r-区间范围，pos-更新位置，val-更新值
void update(const int u, const int l, const int r, const int pos, const int val) {
    if (l == r) { tr[u].val = val; return; }
    if (const int mid = (l + r) >> 1; pos <= mid) update(u<<1, l, mid, pos, val);
    else update(u<<1|1, mid+1, r, pos, val);
    tr[u].val = min(tr[u<<1].val, tr[u<<1|1].val);
}

int query(const int u, const int L, const int R, const int l, const int r) {
    if (l <= L && r >= R) return tr[u].val;
    const int mid = (L + R) >> 1;
    int res = inf;
    if (l <= mid) res = min(res, query(u<<1, L, mid, l, r));
    if (r > mid) res = min(res, query(u<<1|1, mid+1, R, l, r));
    return res;
}

struct node2 { int x, y; } pt[N];
bool cmp(const node2& a, const node2& b) {
    return a.x < b.x;
}
struct node3 { int x1, y1, x2, y2, id; } qu[N];///矩形区域信息和原始ID
bool cmp2(const node3& a, const node3& b) {
    return a.x2 < b.x2;//右边界x2升序
}

int q, k, m, res[N];
void get() {
    memset(tr, 0, sizeof(tr));
    int cnt = 0;
    for (int i = 1; i <= q; ++i) {
        while (cnt <= k && pt[cnt].x <= qu[i].x2) {
            update(1, 1, m, pt[cnt].y, pt[cnt].x);
            ++cnt;
        }
        if (query(1, 1, m, qu[i].y1, qu[i].y2) >= qu[i].x1)
            res[qu[i].id] = 1;
    }
}
int n;
void solve() {
    swap(n, m);
    for (int i = 1; i <= k; ++i)
        swap(pt[i].x, pt[i].y);
    sort(pt+1, pt+k+1, cmp);
    for (int i = 1; i <= q; ++i) {
        swap(qu[i].x1, qu[i].y1);
        swap(qu[i].x2, qu[i].y2);
    }
    sort(qu+1, qu+q+1, cmp2);
}

int main() {
    fast;
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= k; ++i) cin >> pt[i].x >> pt[i].y;
    sort(pt+1, pt+k+1, cmp);
    for (int i = 1; i <= q; ++i) {
        cin >> qu[i].x1 >> qu[i].y1 >> qu[i].x2 >> qu[i].y2;
        qu[i].id = i;
    }
    sort(qu+1, qu+q+1, cmp2); get(); solve(); get();
    for (int i = 1; i <= q; ++i) {
        if (res[i] == 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}