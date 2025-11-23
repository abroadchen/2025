//
// Created by Psy.C on 2025/11/22.
//
/*
 *x存储位置坐标，p存储概率，sub存储计算后的权重值
*l: 从左边开始的最大子段和
r: 从右边开始的最大子段和
sum: 区间总和
best: 区间内最大子段和
 *
*读取概率值，并计算每个区间的权重值：
(x[i] - x[i-1])/2 表示相邻两点间距离的一半
c*p[i]/100 表示成本项
权重 = 距离收益 - 成本
 *
 *时间复杂度为O(m log n)，比朴素的O(mn)方法更高效
 */
#include <cstdio>
#define db double
using namespace std;

constexpr int N = 150050, M = N<<1;
int x[N], p[N];
db sub[N];

db max(const db a, const db b) { return a > b ? a : b; }

struct node {
    double l{}, r{}, sum{}, best{};
    node() = default;
    explicit node(const db o) { l = r = best = max(o, 0); sum = o;}
} st[M];

node operator+(const node& a, const node& b) {//合并两个线段树节点
    node ans;//取左区间最大值、右区间最大值、以及跨越中间的最大值三者中的最大值
    ans.best = max(a.best, b.best);
    ans.best = max(ans.best, a.r + b.l);
    ans.sum = a.sum + b.sum;
    ans.l = max(a.l, a.sum + b.l);//更新左端最大前缀和右端最大后缀：考虑是否跨越中间连接
    ans.r = max(b.r, b.sum + a.r);
    return ans;
}

int ls[M], rs[M], cnt, root;//线段树的左右子节点索引数组、节点计数器和根节点
void build(int& c, const int ss, const int se) {
    c = ++cnt;//c为当前节点引用，ss和se为区间起点和终点
    if (ss == se) { st[c] = node(sub[ss]); return; }//如果是叶节点，用sub[ss]的值创建节点
    const int mid = (ss + se) >> 1;
    build(ls[c], ss, mid);//构建左右子树
    build(rs[c], mid + 1, se);
    st[c] = st[ls[c]] + st[rs[c]];//合并得到当前节点的值
}
//在节点c对应的区间[ss,se]中查询区间[qs,qe]的信息
node get(const int c, const int ss, const int se, const int qs, const int qe) {
    if (qs <= ss && qe >= se) return st[c];//直接返回当前节点信息
    const int mid = (ss + se) >> 1;
    if (qe <= mid) return get(ls[c], ss, mid, qs, qe);//递归查询对应子树
    if (qs > mid) return get(rs[c], mid + 1, se, qs, qe);
    //查询区间跨越中间，需要合并左右两部分的查询结果
    return get(ls[c], ss, mid, qs, qe) + get(rs[c], mid + 1, se, qs, qe);
}

int main() {
    int n, m, c, i, l, r;
    scanf("%d %d %d", &n, &m, &c);//n(点数)、m(查询次数)、c(成本系数)
    for (i = 1; i <= n; ++i) scanf("%d", &x[i]);//读取n个位置坐标
    for (i = 2; i <= n; ++i) {
        scanf("%d", &p[i]);
        sub[i] = static_cast<double>(x[i] - x[i - 1])/2 -
            static_cast<double>(c)*p[i]/100;
    }
    build(root, 2, n);
    db res = 0;
    while (m--) {
        scanf("%d %d", &l, &r);//进行m次查询，每次查询区间[l+1,r]内的最大子段和，并累加到结果中
        res += get(root, 2, n, l + 1, r).best;
    }
    printf("%.12lf\n", res);
    return 0;
}