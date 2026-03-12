//
// Created by Psy.C on 2026/3/12.
//
/**
x, y: 坐标
id: 标识（1表示特殊点，0表示普通点）
operator<: 比较运算符，先按x坐标升序，x相同时按y坐标降序
operator==: 相等判断

叉积判断: 判断三点是否形成左转
返回值为真表示三点形成左转（上凸壳条件）

n: 特殊点数量
m: 普通点数量
p, q: 未使用的参数
tp: 栈顶指针
构建上凸壳:
while (tp && st[tp].y < a[i].y) tp--;: 移除y坐标更小的点
while (tp > 1 && check(st[tp], st[tp-1], a[i])) tp--;: 维护上凸性质
st[++tp] = a[i];: 将当前点加入栈

排序：O((n+m) log(n+m))
去重：O(n+m)
凸包构建：O(n+m)
总体：O((n+m) log(n+m))

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
struct node {
    int x, y, id;
    int operator<(node o) const {
        return x ^ o.x ? x < o.x : y > o.y;
    }
    int operator==(node o) const {
        return x == o.x && y == o.y && id == o.id;
    }
} a[N], st[N];

int check(node o1, node o2, node o3) {
    return 1ll*(o1.x - o2.x) * (o2.y - o3.y) <
        1ll*(o2.x - o3.x) * (o1.y - o2.y);
}

int n, m, p, q, tp;
int main() {
    fast;
    cin >> n >> m >> p >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].x >> a[i].y, a[i].id = 1;
    for (int i = 1; i <= m; ++i)
        cin >> a[i+n].x >> a[i+n].y;
    sort(a+1, a+n+m+1);
    int cnt = unique(a + 1, a + n + m + 1 ) - a - 1;
    for (int i = 1; i <= cnt; ++i) {
        while (tp && st[tp].y < a[i].y) tp--;
        while (tp > 1 && check(st[tp], st[tp-1], a[i])) tp--;
        st[++tp] = a[i];
    }
    for (int i = 1; i <= tp; ++i)
        if (st[i].id) return cout << "Max\n", 0;
    return cout << "Min\n", 0;
}