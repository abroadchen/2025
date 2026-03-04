//
// Created by Psy.C on 2026/3/3.
//
/**
sw: 存储垂直分割线的x坐标集合
sh: 存储水平分割线的y坐标集合
mw: 存储所有垂直段的宽度集合
mh: 存储所有水平段的高度集合
w, h: 初始矩形的宽度和高度
n: 分割操作的次数

在sw中插入左右边界坐标0和w
在sh中插入上下边界坐标0和h
在mw中插入初始宽度w
在mh中插入初始高度h
循环n次，处理每次分割操作
读入操作类型c('H'或'V')和分割位置x

在sh中插入新的水平分割线位置x
找到新分割线左边相邻的分割线坐标a和右边相邻的分割线坐标b
从mh中删除原来的区间长度(b-a)
向mh中添加两个新区间长度：(x-a)和(b-x)
在sw中插入新的垂直分割线位置x
找到新分割线左边相邻的分割线坐标a和右边相邻的分割线坐标b
从mw中删除原来的区间长度(b-a)
向mw中添加两个新区间长度：(x-a)和(b-x)

获取mh中的最大值（最大的高度区间）
获取mw中的最大值（最大的宽度区间）
输出最大矩形面积（最大高度×最大宽度）

时间复杂度为O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

set<int> sw, sh;
multiset<int> mw, mh;
int w, h, n;
int main() {
    fast;
    cin >> w >> h >> n;
    sw.insert(0); sw.insert(w);
    sh.insert(0); sh.insert(h);
    mw.insert(w); mh.insert(h);
    for (int i = 0; i < n; ++i) {
        char c; int x; cin >> c >> x;
        if (c == 'H') {
            sh.insert(x);
            const int a = *(--sh.find(x)), b = *(++sh.find(x));
            mh.erase(mh.find(b - a));
            mh.insert(x - a);
            mh.insert(b - x);
        } else {
            sw.insert(x);
            const int a = *(--sw.find(x)), b = *(++sw.find(x));
            mw.erase(mw.find(b - a));
            mw.insert(x - a);
            mw.insert(b - x);
        }
        const ll mxh = *(--mh.end()), mxw = *(--mw.end());
        cout << mxh*mxw << '\n';
    }
    return 0;
}