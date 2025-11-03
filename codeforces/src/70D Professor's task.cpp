//
// Created by Psy.C on 2025/11/2.
//
/*
 *q(查询次数)、op(操作类型)、x和y(坐标值)
 *
*重载叉积函数，计算相对于点o的向量oa和ob的叉积
先将点a和b平移到以o为原点的坐标系中
然后调用两参数版本的叉积函数
 *
*定义结构体lh，用于维护凸包
hull是一个多重集合，存储凸包上的点
 *
*判断点p是否在凸包内部或边界上的函数
使用lower_bound找到不小于点p的第一个点
如果找不到，则点p不在凸包内
如果是第一个点，则只有当p等于该点时才在凸包内
否则计算叉积判断点是否在凸包内(叉积非负表示在左侧或线上)
 *
*插入点p到凸包中的函数
如果点p已经在凸包内，则不需要插入
 *
*找到插入位置
从该位置开始，移除所有使凸包性质不成立的点
当下一个点存在且相对于当前点和新点的叉积非正时，删除当前点
*处理插入点之前的点
当前一个点存在且相对于当前点和新点的叉积非负时，删除当前点
 *将点p插入到凸包中
 *
 *
*如果操作类型是1：将点(x,y)插入h1，将点(-x,-y)插入h2
如果操作类型是2：检查点(x,y)是否在h1中且(-x,-y)是否在h2中，输出结果
 *
 */
#include <iostream>
#include <set>
using namespace std;

typedef long long ll;
using P = pair<ll, ll>;
int q, op, x, y;
//定义叉积(cross product)函数，计算两个二维向量的叉积
ll cr(P a, P b) { return a.first * b.second - a.second * b.first; }

ll cr(P a, P b, P o) {
    a.first -= o.first, a.second -= o.second;
    b.first -= o.first, b.second -= o.second;
    return cr(a, b);
}

struct lh {
    multiset<P> hull;

    bool inside(P p) {
        auto it = hull.lower_bound(p);
        if (it == hull.end()) return false;
        if (it == hull.begin()) return p == *it;
        return cr(*it, p, *prev(it)) >= 0;
    }
    void insert(P p) {
        if (inside(p)) return;
        auto it = hull.lower_bound(p);
        if (it != hull.end()) {
            while (next(it) != hull.end() &&
                cr(*it, *next(it), p) <= 0) {
                it = hull.erase(it);
            }
        }
        if (it != hull.begin()) {
            while (--it != hull.begin() &&
                cr(*it, *prev(it), p) >= 0) {
                it = hull.erase(it);
            }
        }
        hull.emplace(p);
    }
} h1, h2;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> q;
    while (q--) {
        cin >> op >> x >> y;
        if (op == 1) {
            h1.insert(P(x, y));
            h2.insert(P(-x, -y));
        } else {
            cout << (h1.inside(P(x, y)) &&
                h2.inside(P(-x, -y)) ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}