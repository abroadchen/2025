//
// Created by Psy.C on 2025/11/28.
//
/*
* p，用来存储原始点集；
变量 h 用于临时保存每次查询的点
 *
*判断点 x 在由点 u 指向点 v 的直线的方向上是在左侧还是右侧：
返回正数表示在左边，
负数在右边，
零在线上
 *
*检查给定点 x 是否位于凸包内部或边界外侧。
参数说明：
num: 当前考虑的点数量；
c[]: 已排序好的点集合（通常是构成凸包的点）；
x: 待检测的点
 *
*若当前三点方向不满足某种条件（即点在某边的右侧），则将右界缩小至 mid；
否则左界扩大至 mid + 1
 *如果 r == 1 或者点在最后一条边上或者在相邻两条边之间没有形成“凹”的形状，则不在凸包内
 *
*在二分查找结束后，r 指向凸包边界上的一个特定点
这个点是通过二分查找找到的关键边界点之一
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+10;
int n, m;

struct node {
    ll x{}, y{};
    node() = default;
    node(const ll x, const ll y) : x(x), y(y) {}
    void read() { cin >> x >> y; }
    bool operator<(const node& rhs) const {
        if (y == rhs.y) return x > rhs.x;
        return y > rhs.y;
    }
} p[N], h;

node operator-(const node& u, const node& v) { return {u.x - v.x, u.y - v.y}; }
ll det(const node& u, const node& v) { return u.x * v.y - u.y * v.x; }//判断方向关系
ll dir(const node& x, const node& u, const node& v) { return det(u - x, v - x); }

bool ok(const int num, node c[], const node x) {
    int l(1), r(num - 1);
    while (l < r) {
        const int mid = (l + r) / 2;
        if (dir(c[0], c[mid], x) <= 0) r = mid;
        else l = mid + 1;
    }
    if (r == 1 || dir(c[0], c[num - 1], x) >= 0 ||
        dir(c[r], c[r - 1], x) >= 0) return false;
    return true;
}

int main() {
    fast;
    cin >> n;
    for (int i = n - 1; i >= 0; --i) p[i].read();
    cin >> m;
    for (int i = 0; i < m; ++i) {
        h.read();
        if (!ok(n, p, h)) { cout << "NO" << '\n'; return 0; }
    }
    cout << "YES" << '\n';
    return 0;
}