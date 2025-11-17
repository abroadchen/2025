//
// Created by Psy.C on 2025/11/17.
//
/*
*lk：存储幸运数字的向量
a：存储原始数据的向量
*l, r：区间左右端点
cnt：区间内满足特定条件的元素个数
d：区间内的最小差值
laz：懒惰标记，用于延迟更新
 *
*设置节点o的值：
找到不小于a[i]的最小幸运数字
计算差值d作为该位置的最小距离
如果差值为0（即a[i]本身就是幸运数字），cnt设为1，否则为0
清空懒惰标记
*维护节点o的信息：
cnt为左右子树cnt之和
d为左右子树d的最小值
o<<1表示左子节点，o<<1|1表示右子节点
*构建线段树：
设置节点区间[l,r]
如果是叶子节点，调用set函数
否则递归构建左右子树，然后维护当前节点
 *
 *应用延迟更新：将增量f应用到节点o
 *传播懒惰标记：将当前节点的懒惰标记传递给子节点
*更新区间[l,r]内的值，增加f：
如果当前区间完全包含在[l,r]内且最小差值大于f，直接应用懒惰更新
如果是叶子节点，直接更新数组a并重新设置节点值
否则传播懒惰标记，递归更新子节点，维护当前节点
*查询区间[l,r]内满足条件的元素个数：
如果当前区间完全包含在[l,r]内，返回cnt
否则递归查询左右子树并返回结果之和
 *
*生成所有幸运数字（从4和7开始）
排序幸运数字向量
添加一个大数1e9作为哨兵
*读取数组大小n和操作数m
读取数组元素
创建线段树并构建
*处理m个操作：
"add"操作：在区间[l,r]内所有元素增加d
其他操作：查询区间[l,r]内有多少个元素是幸运数字
 *使用线段树和懒惰传播实现O(log n)的复杂度
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> lk, a;

struct node { int l, r, cnt, d, laz; };
using Segtree = vector<node>;

void dfs(int x) {
    if (x > 1e4) return;
    lk.push_back(x);
    dfs(x * 10 + 4);
    dfs(x * 10 + 7);
}

void set(Segtree& t, int o) {
    int i = t[o].l;
    t[o].d = *lower_bound(lk.begin(), lk.end(), a[i]) - a[i];
    t[o].cnt = t[o].d == 0 ? 1 : 0;
    t[o].laz = 0;
}

void maintain(Segtree& t, int o) {
    t[o].cnt = t[o<<1].cnt + t[o<<1|1].cnt;
    t[o].d = min(t[o<<1].d, t[o<<1|1].d);
}

void build(Segtree& t, int o, int l, int r) {
    t[o].l = l, t[o].r = r;
    if (l == r) { set(t, o); return; }
    int m = (l + r) / 2;
    build(t, o<<1, l, m);
    build(t, o<<1|1, m + 1, r);
    maintain(t, o);
}

void apply(Segtree& t, int o, int f) { t[o].d -= f; t[o].laz += f; }
void spread(Segtree& t, int o) {
    int f = t[o].laz;
    if (f == 0) return;
    apply(t, o<<1, f);
    apply(t, o<<1|1, f);
    t[o].laz = 0;
}


void update(Segtree& t, int o, int l, int r, int f) {
    if (t[o].l >= l && t[o].r <= r && t[o].d > f) {
        apply(t, o, f);
        return;
    }
    if (t[o].l == t[o].r) {
        a[t[o].l] += t[o].laz + f;
        set(t, o);
        return;
    }
    spread(t, o);
    int m = (t[o].l + t[o].r) / 2;
    if (l <= m) update(t, o<<1, l, r, f);
    if (m < r) update(t, o<<1|1, l, r, f);
    maintain(t, o);
}

int query(Segtree& t, int o, int l, int r) {
    if (t[o].l >= l && t[o].r <= r) return t[o].cnt;
    int m = (t[o].l + t[o].r) / 2, res = 0;
    if (l <= m) res += query(t, o<<1, l, r);
    if (m < r) res += query(t, o<<1|1, l, r);
    return res;
}

int main() {
    dfs(4); dfs(7);
    sort(lk.begin(), lk.end());
    lk.push_back(1e9);//确保 lower_bound 总能返回有效迭代器
    int n, m; cin >> n >> m; a.resize(n);
    for (int& x : a) cin >> x;

    Segtree t(4 * n + 5);
    build(t, 1, 0, n - 1);
    while (m--) {
        string s; cin >> s;
        int l, r; cin >> l >> r; l--, r--;
        if (s == "add") {
            int d; cin >> d;
            update(t, 1, l, r, d);
        } else cout << query(t, 1, l, r) << '\n';
    }
    return 0;
}