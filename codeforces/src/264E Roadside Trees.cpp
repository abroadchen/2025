//
// Created by Psy.C on 2025/12/21.
//
/*
*ls: 左子节点索引 (rt*2)
rs: 右子节点索引 (rt*2+1)
lson, rson: 递归调用时的参数简写
S: 线段树数组大小
mx[S]: 存储线段树节点最大值
f[N]: 存储位置对应的函数值
update(rt): 更新节点值为左右子节点的最大值
 *
*在区间[l,r]的节点rt中，将位置p的值修改为v
如果是叶子节点，直接赋值
否则递归修改对应子树，然后更新当前节点
 *
*查询区间[0,R]内的最大值
如果当前区间完全在查询范围内，返回当前节点值
否则递归查询子区间并返回最大值
 *
 *在位置p插入新元素，值为其前面最大值加1
 *
*读取n(序列长度)和m(操作次数)
pos[N]: 存储高度对应的位置
h[N]: 存储位置对应的高度
st: 有序集合，维护当前存在的位置
 *
 *操作类型1：添加元素
*计算插入位置p和高度ht
更新位置和高度映射关系
将位置加入集合
*清除影响的节点值
重新计算相关位置的值
输出当前最长递增子序列长度
*操作类型2：删除元素
删除最后k个元素
更新相关数据结构
重新计算受影响元素的值
输出结果
 *
*tp: 主要维护位置维度的信息
th: 主要维护高度维度的信息
*tp.f[]: 存储每个位置对应的 LIS 长度值
th.f[]: 存储每个高度对应的 LIS 长度值
 */
#include <iostream>
#include <set>
#include <cctype>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200015
using namespace std;

struct sgt {
#define ls rt<<1
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs
#define S N<<2
    int mx[S], f[N];
#undef S
#define update(rt) mx[rt] = max(mx[ls], mx[rs])
    void modify(const int l, const int r, const int rt, const int p, const int v) {
        if (l == r) { mx[rt] = v; return; }
        const int m = (l + r) >> 1;
        if (p <= m) modify(lson, p, v);
        else modify(rson, p, v);
        update(rt);
    }
    int query(const int l, const int r, const int rt, const int R) {
        if (r <= R) return mx[rt];
        const int m = (l + r) >> 1;
        if (m < R) return max(query(lson,R), query(rson,R));
        return query(lson, R);
    }
    void insert(const int p, const int n) {
        modify(0, n, 1, p, (f[p] = query(0, n, 1, p - 1) + 1));
    }
} tp, th;

int read() {
    int cur = 0; char c; cin.get(c);
    for (; !isdigit(c); cin.get(c)){}
    for (; isdigit(c); cur = (cur<<3)+(cur<<1)+(c&15), cin.get(c)){}
    return cur;
}

int main() {
#define sp 0,n,1
#define sh 0,m+10,1
    fast;
    int n, m, pos[N], h[N]; cin>>n>>m;
    set<int> st;
    for (int t = 1; t <= m; ++t) {
        if (read() == 1) {
            int p = n - read() + 1;
            const int ht = t + 10 - read();
            pos[ht] = p, h[p] = ht, st.insert(p);//高度与位置的双向映射
            for (int i = ht + 1; i <= ht + 9; ++i) if (pos[i]) {//保留当前位置
                tp.modify(sp, pos[i], 0);
            }
            for (int i = ht; i <= ht + 9; ++i) if (pos[i]) {//包括当前位置
                tp.insert(pos[i], n);//重新计算位置维度的值
                th.f[i] = tp.f[pos[i]];//将位置维度的LIS长度值同步到高度维度
                th.modify(sh, i, th.f[i]);//更新高度维度线段树
            }
            cout << tp.mx[1] << '\n';
        } else {
            int k = read();
            auto it = st.end();
            while (k--) --it, th.modify(sh, h[*it], 0);
            tp.modify(sp, *it, 0), pos[h[*it]] = 0;
            for (st.erase(it++); it != st.end(); ++it) {
                th.insert(h[*it], m+10);//重新计算高度为h[*it]的元素的LIS长度
                tp.f[*it] = th.f[h[*it]];//同步到位置维度
                tp.modify(sp, *it, tp.f[*it]);//更新位置维度的线段树
            }
            cout << tp.mx[1] << '\n';
        }
    }
    return 0;
}