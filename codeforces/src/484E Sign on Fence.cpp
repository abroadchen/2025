//
// Created by Psy.C on 2026/2/17.
//
/**
l, r: 左右子节点索引
lc: 从左端开始的连续1的长度
rc: 从右端开始的连续1的长度
c: 区间内最长连续1的长度

t[now].lc: 从左端开始的连续1长度
如果左子树全是1，则可以延伸到右子树
t[now].rc: 从右端开始的连续1长度
如果右子树全是1，则可以延伸到左子树
t[now].c: 最长连续1长度 = max(左端连续, 右端连续, 跨越中点, 左子树内, 右子树内)

res: 全局最大连续长度
lst: 上次查询的右端连续长度

预处理：O(n log n)
每次询问：O(log²n)
总时间复杂度：O(n log n + m log²n)
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;


template<typename T>
void read(T& a) {
    char c = getchar(); T x = 0, f = 1;
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = (x<<1)+(x<<3)+(c&15); c = getchar(); }
    a = f*x;
}

constexpr ll N = 2e5+700;
struct node { int l, r, lc, rc, c; } t[N*40];

int cnt=0;
///pre基础上插入pos位置的值，生成新版本now
void update(int& now, const int pre, const int l, const int r, const int pos) {
    t[now=++cnt] = t[pre];//复制前一个版本
    if (l == r) {
        t[now].c = t[now].lc = t[now].rc = 1;
        return;
    }
    const int mid = (l + r)>>1;
    if (pos <= mid) update(t[now].l, t[pre].l, l, mid, pos);
    else update(t[now].r, t[pre].r, mid+1, r, pos);
    const int ls = t[now].l, rs = t[now].r;
    if (t[ls].lc == mid-l+1) t[now].lc = t[ls].lc + t[rs].lc;
    else t[now].lc = t[ls].lc;
    if (t[rs].rc == r-mid) t[now].rc = t[rs].rc + t[ls].rc;
    else t[now].rc = t[rs].rc;
    t[now].c = max(t[now].lc, t[now].rc);
    t[now].c = max(t[now].c, t[ls].rc + t[rs].lc);
    t[now].c = max(t[now].c, t[rs].c);
    t[now].c = max(t[now].c, t[ls].c);
}

int res = 0, lst = 0;
void query(const int now, const int l, const int r, const int x, const int y) {
    if (x <= l && y >= r) {
        res = max(res, t[now].c);
        res = max(res, t[now].lc + lst);
        if (t[now].rc == r-l+1) lst += t[now].rc;
        else lst = t[now].rc;
        return;
    }
    const int mid = (l + r) >> 1;
    if (x <= mid) query(t[now].l, l, mid, x, y);
    if (y > mid) query(t[now].r, mid+1, r, x, y);
}

struct node2 {
    int x, id;//x: 值，id: 原始索引
    friend bool operator<(const node2 a, const node2 b) {
        return a.x < b.x;
    }
} q[N];

int rt[N*40];
ll n, m;
int main() {
    read(n);
    for (int i = 1; i <= n; ++i) { read(q[i].x); q[i].id = i; }
    sort(q + 1, q + n + 1);
    for (int i = n; i >= 1; --i)
        update(rt[i], rt[i+1], 1, n, q[i].id);
    read(m);
    for (int i = 1, x, y, w; i <= m; ++i) {
        read(x), read(y), read(w);//查询区间[x,y]和目标长度w
        int l = 1, r = n, ans = 0;
        while (l <= r) {
            const int mid = (l + r) >> 1;
            res = lst = 0;
            query(rt[mid], 1, n, x, y);
            if (res >= w) { ans = mid; l = mid + 1; }
            else r = mid - 1;
        }
        printf("%d\n", q[ans].x);
    }
    return 0;
}