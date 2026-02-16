//
// Created by Psy.C on 2026/2/16.
//
/**
n: 数组长度
l: 上限
x, y: 两个目标差值
g: 标记是否已存在差值为x的数对
b: 标记是否已存在差值为y的数对

时间复杂度：
O(n)，主要是遍历数组的时间
map查找为O(log n)，整体仍为O(n)
空间复杂度：
O(n)，主要是map和vector的空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 110000;
int n, l, x, y, a[N];
map<int, int> mp;//快速查找某个值是否存在
vector<int> v;//存储需要添加的数

int main() {
    fast;
    cin >> n >> l >> x >> y;
    bool g = false, b = false;
    int i, t;
    for (i = 1; i <= n; ++i) {
        cin >> t; a[i] = t; mp[t] = 1;
        if (mp.contains(t-x)) g = true;// 如果t-x存在，则已存在差值为x的数对
        if (mp.contains(t-y)) b = true;
    }
    if (!g && !b) {//既不存在差值x也不存差值y
        for (i = 1; i <= n; ++i) {
            if (a[i] - x >= 0) {//是否可以通过a[i] - x来满足条件
                t = a[i] - x;//可能的插入值
                ///如果t-y存在，那么t和t-y的差值就是y，加上t就能同时满足x和y
                if (mp.contains(t - y)) {
                    v.push_back(t);
                    break;
                }
                if (mp.contains(t + y)) {//如果t+y存在，那么t+y和t的差值就是y
                    v.push_back(t);
                    break;
                }
            }
            if (a[i] + x <= l) {//是否可以通过a[i] + x来满足条件
                t = a[i] + x;
                if (mp.contains(t - y)) {
                    v.push_back(t);
                    break;
                }
                if (mp.contains(t + y)) {
                    v.push_back(t);
                    break;
                }
            }
        }
        //找不到同时满足的方案，添加x和y两个数
        if (i > n) { v.push_back(x); v.push_back(y); }
    }
    else if (!g) v.push_back(x);//不存在x但存在y，只需添加x
    else if (!b) v.push_back(y);//不存在y但存在x，只需添加y
    cout << v.size() << '\n';//需要添加的数的个数
    for (i = 0; i < v.size(); ++i)
        cout << v[i] << " \n"[i==v.size()-1];
    return 0;
}