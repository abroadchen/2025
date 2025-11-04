//
// Created by Psy.C on 2025/11/4.
//
/*
*n: 区间长度，q: 查询次数
x, y: 临时变量
ct: 线段树节点计数器，初始为1
t[]: 线段树节点值数组
ls[], rs[]: 线段树左右子节点数组
a: 记录点是否被标记的映射
b: 记录点对应位置的映射
*Node结构体表示区间[l,r]
比较运算符：按区间长度降序排列，长度相同时按左端点降序
*Node2结构体表示区间[l,r]
比较运算符：按左端点升序排列，左端点相同时按右端点升序
*s: 按区间长度排序的集合
s2: 按区间位置排序的集合
 *
*线段树查询函数：查询区间[rl,rr]内的值之和
rt: 当前节点，l,r: 当前区间范围
如果无节点或无交集返回0
如果完全包含返回节点值
否则递归查询左右子树
 *
 *线段树上传函数：更新当前节点值为左右子节点值之和
 *
*线段树更新函数：在位置x增加k
如果x不在当前区间范围，直接返回
如果是叶子节点，直接更新
如果子节点不存在则创建
递归更新子树并上传结果
 *
 *初始化集合，插入完整区间[1,n]
 *
*循环处理q次操作
如果x=0，表示查询操作：读取区间[x,y]并输出查询结果
*否则为标记操作：翻转a[x]的值
如果a[x]变为1(标记该点)：
*取出最长区间p
从两个集合中删除该区间
将x标记在区间中点位置
 *如果左半部分存在，插入新的左右区间到两个集合
 *在线段树中更新该位置
*如果a[x]变为0(取消标记)：
找到位置b[x]在s2中的位置
初始化左右边界为b[x]
 *检查左边相邻区间是否可以合并
 *检查右边相邻区间是否可以合并
*插入合并后的新区间
在线段树中取消标记
 */
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll N = 2e5+10;
int n, q, x, y, ct(1), t[N<<4], ls[N<<4], rs[N<<4];
map<ll, ll> a, b;
struct Node {
    ll l, r;
    bool operator<(const Node& x) const {
        return r - l == x.r - x.l ? l > x.l : r - l > x.r - x.l;
    }
};
struct Node2 {
    ll l, r;
    bool operator<(const Node2& x) const {
        return l != x.l ? l < x.l : r < x.r;
    }
};
set<Node> s;
set<Node2> s2;

ll query(ll rt, ll l, ll r, ll rl, ll rr) {
    if (!rt || rl > r || rr < l) return 0;
    if (rl <= l && r <= rr) return t[rt];
    ll mid = (l + r) >> 1;
    return query(ls[rt], l, mid, rl, rr) +
        query(rs[rt], mid + 1, r, rl, rr);
}

void up(ll rt) { t[rt] = t[ls[rt]] + t[rs[rt]]; }

void update(ll rt, ll l, ll r, ll x, ll k) {
    if (l > x || x > r) return;
    if (l == r) { t[rt] += k; return; }
    if (!ls[rt]) ls[rt] = ++ct;
    if (!rs[rt]) rs[rt] = ++ct;
    ll mid = (l + r) >> 1;
    update(ls[rt], l, mid, x, k);
    update(rs[rt], mid + 1, r, x, k);
    up(rt);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    s.insert({1, n});
    s2.insert({1, n});

    while (q--) {
        cin >> x;
        if (!x) {
            cin >> x >> y;
            cout << query(1, 1, n, x, y) << "\n";
        } else {
            a[x] ^= 1;
            if (a[x]) {
                Node p = *s.begin(); s2.erase({p.l, p.r});
                s.erase(s.begin());
                b[x] = (p.l + p.r + 1) / 2;
                if (p.l <= b[x] - 1) s.insert({p.l, b[x] - 1}),
                    s2.insert({p.l, b[x] - 1});
                if (b[x] + 1 <= p.r) s.insert({b[x] + 1, p.r}),
                    s2.insert({b[x] + 1, p.r});
                update(1, 1, n, b[x], 1);
            } else {
                auto it = s2.lower_bound({b[x], 0});
                ll l = b[x], r = b[x];
                if (it != s2.begin()) {
                    auto it1 = --it; it++;
                    if (it1->r + 1 == b[x]) s.erase({it1->l, it1->r}),
                        s2.erase({it1->l, it1->r}),
                        l = it1->l;
                }
                if (it != s2.end() && it->l - 1 == b[x]) {
                    s.erase({it->l, it->r});
                    s2.erase({it->l, it->r});
                    r = it->r;
                }
                s.insert({l, r});
                s2.insert({l, r});
                update(1, 1, n, b[x], -1);
            }
        }
    }
    return 0;
}