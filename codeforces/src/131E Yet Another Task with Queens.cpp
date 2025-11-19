//
// Created by Psy.C on 2025/11/19.
//
/*
*遍历排序后的节点：
如果当前节点与前一个节点有相同的x坐标，增加计数
如果当前节点与后一个节点有相同的x坐标，增加计数
这是在统计在同一垂直线上的相邻点
 *
 *
*如果当前节点与前一个节点有相同的y坐标，增加计数
如果当前节点与后一个节点有相同的y坐标，增加计数
这是在统计在同一水平线上的相邻点
 *
*如果当前节点与前一个节点在同一条对角线(x-y=k)上，增加计数
如果当前节点与后一个节点在同一条对角线(x-y=k)上，增加计数
 *
*如果当前节点与前一个节点在同一条反对角线(x+y=k)上，增加计数
如果当前节点与后一个节点在同一条反对角线(x+y=k)上，增加计数
 *
 */
#include <ranges>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin>>n>>m;
    struct node { int i, x, y; };
    vector<node> v(m);
    rep(i,m) { cin>>v[i].x>>v[i].y; v[i].i = i; }//设置索引
    vector<int> ans(m);//存储每个点的计数
    ranges::sort(v, {}, [](const node& i) {
        return make_pair(i.x, i.y);//x坐标为主键、y坐标为次键对节点进行排序
    });
    rep(i,m) {
        if (i and v[i - 1].x == v[i].x) ++ans[v[i].i];
        if (i + 1 < m and v[i + 1].x == v[i].x) ++ans[v[i].i];
    }
    ranges::sort(v, {}, [](const node& i) {
        return make_pair(i.y, i.x);
    });
    rep(i,m) {
        if (i and v[i - 1].y == v[i].y) ++ans[v[i].i];
        if (i + 1 < m and v[i + 1].y == v[i].y) ++ans[v[i].i];
    }
    ranges::sort(v, {}, [](const node& i) {
        return make_pair(i.x - i.y, i.y);//(x-y)为主键、y坐标为次键
    });
    rep(i,m) {
        if (i and v[i - 1].x - v[i - 1].y == v[i].x - v[i].y) ++ans[v[i].i];
        if (i + 1 < m and v[i + 1].x - v[i + 1].y == v[i].x - v[i].y) ++ans[v[i].i];
    }
    ranges::sort(v, {}, [](const node& i) {
        return make_pair(i.x + i.y, i.y);
    });
    rep(i,m) {
        if (i and v[i - 1].x + v[i - 1].y == v[i].x + v[i].y) ++ans[v[i].i];
        if (i + 1 < m and v[i + 1].x + v[i + 1].y == v[i].x + v[i].y) ++ans[v[i].i];
    }
    array<int, 9> cnt{};
    for (int i : ans) ++cnt[i];//统计ans中各个计数值出现的次数
    for (int i : cnt) cout << i << ' ';//输出统计结果
    return 0;
}