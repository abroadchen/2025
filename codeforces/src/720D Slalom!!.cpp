//
// Created by Psy.C on 2026/4/22.
//
/**
M = 1e5+7：常量M，表示最大矩形数量
N = 1e6+7：常量N，表示线段树数组大小
坐标x、左右边界l/r、类型k
按x坐标升序排列
若x相同，则按k值升序排列
若x和k都相同，则按l降序排列
tag[]：懒惰标记数组，用于区间更新
s[]：存储实际值的数组
siz[]：大小数组，记录区间内元素个数

向下传递懒惰标记
如果标记为1：清空子节点s值，设置标记为1，更新siz为区间长度
如果标记为2：清空子节点s值，设置标记为2，siz设为0
向上更新节点信息
s[x] = 左右子节点s值之和
siz[x] = 左右子节点siz之和
对结果取模防止溢出
单点修改操作
在位置a处修改值为b
递归到叶子节点进行修改
区间更新操作
将区间[a,b]更新为某种状态(c=1或c=2)
如果完全覆盖当前区间则打标记，否则继续向下更新
区间查询操作
查询区间[a,b]内的s值总和
返回结果并取模
查询区间[a,b]内siz值总和
类似query函数，但返回的是siz数组的值
找到第a个有效位置
根据siz数组二分查找对应位置

读入n(行数)、m(列数)、k(矩形数)
处理k个矩形，每个矩形(a,b,c,d)转换为3个事件
k=2: 在a位置开始覆盖区间[b,d]
k=1: 在a+1位置取消覆盖区间[b,d]
k=3: 在c+1位置结束覆盖区间[b,d]
添加辅助事件，处理边界情况
按照自定义规则排序所有事件
初始化，在位置1处设置值为1
按x坐标和k值分组处理事件
k=2: 处理覆盖逻辑，找到特定位置并更新
k=1: 区间覆盖操作
k=3: 区间清除操作
查询最后在位置m的值并输出
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int M = 1e5+7, N = 1e6+7, mod = 1e9+7;

struct node {
    int x, l, r, k;
    bool operator<(const node &o) const {
        return x == o.x ? (k == o.k ? l > o.l : k < o.k) : x < o.x;
    }
} p[M*3];

#define ls x<<1
#define rs (x<<1|1)
#define mid ((l+r)>>1)
int tag[N<<2], s[N<<2], siz[N<<2];
void pushdown(int l, int r, int x) {
    if (tag[x] == 1) {
        s[ls] = s[rs] = 0, tag[ls] = tag[rs] = 1;
        siz[ls] = mid-l+1, siz[rs] = r-mid, tag[x] = 0;
    }
    if (tag[x] == 2)
        s[ls] = s[rs] = 0, tag[ls] = tag[rs] = 2, siz[ls] = siz[rs] = 0, tag[x] = 0;
}
void push_up(int x) {
    s[x] = s[ls] + s[rs], siz[x] = siz[ls] + siz[rs];
    if (s[x] >= mod) s[x] -= mod;
}
void modify(int l, int r, int x, int a, int b) {
    if (l == r) { s[x] = b; return; }
    pushdown(l, r, x);
    if (a <= mid) modify(l, mid, ls, a, b);
    else modify(mid+1, r, rs, a, b);
    push_up(x);
}
void update(int l, int r, int x, int a, int b, int c) {
    if (a <= l && r <= b) {
        if (c == 1) tag[x] = 1, siz[x] = r-l+1, s[x] = 0;
        else tag[x] = 2, siz[x] = s[x] = 0;
        return;
    }
    pushdown(l, r, x);
    if (a <= mid) update(l, mid, ls, a, b, c);
    if (b > mid) update(mid+1, r, rs, a, b, c);
    push_up(x);
}
int query(int l, int r, int x, int a, int b) {
    if (a <= l && r <= b) return s[x];
    pushdown(l, r, x);
    int ret = 0;
    if (a <= mid) ret += query(l, mid, ls, a, b);
    if (b > mid) ret += query(mid+1, r, rs, a, b);
    if (ret >= mod) ret -= mod;
    return ret;
}
int dfs(int l, int r, int x, int a, int b) {
    if (a <= l && r <= b) return siz[x];
    pushdown(l, r, x);
    if (b <= mid) return dfs(l, mid, ls, a, b);
    if (a > mid) return dfs(mid+1, r, rs, a, b);
    return dfs(l, mid, ls, a, b) + dfs(mid+1, r, rs, a, b);
}
int find(int l, int r, int x, int a) {
    if (l == r) return l;
    pushdown(l, r, x);
    if (a <= siz[ls]) return find(l, mid, ls, a);
    return find(mid+1, r, rs, a-siz[ls]);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k, i, a, b, c, d, tot;
int main() {
    n = rd(), m = rd(), k = rd();
    for (i = 1; i <= k; i++) {
        a = rd(), b = rd(), c = rd(), d = rd();
        p[++tot].x = a, p[tot].l = b, p[tot].r = d, p[tot].k = 2;
        p[++tot].x = a+1, p[tot].l = b, p[tot].r = d, p[tot].k = 1;
        p[++tot].x = c+1, p[tot].l = b, p[tot].r = d, p[tot].k = 3;
    }
    p[++tot].x = 1, p[tot].l = 2, p[tot].r = m, p[tot].k = 1;
    p[++tot].x = 1, p[tot].l = 2, p[tot].r = m, p[tot].k = 3;
    p[++tot].x = n+1, p[tot].l = 1, p[tot].r = m-1, p[tot].k = 2;
    sort(p + 1, p + tot + 1);
    modify(1, m, 1, 1, 1);
    for (a = 1; a <= tot; a = b+1) {
        for (b = a; b < tot && p[b+1].x == p[b].x && p[b+1].k == p[b].k; b++) {}
        if (p[a].k == 2) {
            for (i = a; i <= b; i++) if (p[i].r != m) {
                c = dfs(1, m, 1, 1, p[i].r+1);
                if (!c) d = 0; else d = find(1, m, 1, c);
                if (d != p[i].r+1)
                    modify(1, m, 1, p[i].r+1, query(1, m, 1, d+1, p[i].r+1));
            }
        } else if (p[a].k == 1) {
            for (i = a; i <= b; i++)
                update(1, m, 1, p[i].l, p[i].r, 1);
        } else {
            for (i = a; i <= b; i++)
                update(1, m, 1, p[i].l, p[i].r, 2);
        }
    }
    printf("%d", query(1, m, 1, m, m));
    return 0;
}