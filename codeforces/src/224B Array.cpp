//
// Created by Psy.C on 2025/12/9.
//
/*
 *
*正向遍历数组a：
将每个元素插入集合t中（自动去重）
如果集合t的大小等于m（找到了m个不同的元素）：
设置标志f1为true
记录当前位置i到变量j
跳出循环
 *
*从位置j开始反向遍历数组a到位置1：
将每个元素插入集合s中（自动去重）
如果集合s的大小等于m（找到了m个不同的元素）：
设置标志f2为true
记录当前位置i到变量k
跳出循环
 *
*如果两个标志都为true（即前后两次都能找到m个不同元素）：
输出k和j（最短连续子数组的起始和结束位置）
否则输出-1 -1（表示无法找到包含m个不同元素的连续子数组）
 *
 *时间复杂度为O(n)，空间复杂度为O(m)
 */
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

set<int> s, t;//存储不重复的整数

int main() {
    fast;
    int n, m, a[N], j = 0, k = 0; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    bool f1 = false, f2 = false;
    for (int i = 1; i <= n; ++i) {
        t.insert(a[i]);
        if (t.size() == m) { f1 = true; j = i; break; }
    }
    for (int i = j; i >= 1; --i) {
        s.insert(a[i]);
        if (s.size() == m) { f2 = true; k = i; break; }
    }
    if (f1 == true && f2 == true) cout << k << ' ' << j << '\n';
    else cout << -1 << ' ' << -1 << '\n';
    return 0;
}