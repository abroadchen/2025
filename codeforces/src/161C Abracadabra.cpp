//
// Created by Psy.C on 2025/11/26.
//
/*
*l1, r1: 第一个区间的左右端点
l2, r2: 第二个区间的左右端点
step: 递归深度，默认为30
 *如果任一区间无效（左端点>右端点），返回0
*l: 重叠区间的左端点（两个区间左端点的最大值）
r: 重叠区间的右端点（两个区间右端点的最小值）
x: 重叠区间的长度（如果有效则为r-l+1，否则为0）
*如果区间1完全包含区间2，或区间2完全包含区间1
直接返回重叠长度x
 *
*计算中点：mid = 2^(step-1)
初始化结果为当前重叠长度
 *
*递归计算左半部分的重叠：
将两个区间都限制在[1, mid-1]范围内
递归深度减1
 *
*递归计算左半部分与右半部分的重叠：
区间1限制在左半部分[1, mid-1]
区间2映射到右半部分，然后平移到左半部分进行计算
 *
*递归计算右半部分与左半部分的重叠：
区间1映射到左半部分
区间2限制在左半部分
 *
*递归计算右半部分的重叠：
两个区间都映射到左半部分进行计算
 *
 *
*右半部分映射到左半部分
max(l1, mid + 1) - mid  // 将[l1,mid]或[mid+1,r1]映射到左半部分
max(r1, mid) - mid      // 将右端点映射到左半部分坐标系
 *
 *
 *O(log(max(r1,r2)))，因为每次递归将问题规模减半
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int dfs(const int l1, const int r1, const int l2, const int r2, const int step=30) {
    if (l1 > r1 || l2 > r2) return 0;
    const int l = max(l1, l2), r = min(r1, r2),
    x = l <= r ? r - l + 1 : 0;
    if (l1 <= l2 && r1 >= r2 || l1 >= l2 && r1 <= r2) return x;
    const int mid = 1 << (step - 1); int res = x;
    res = max(res,
        dfs(min(l1, mid), min(r1, mid - 1),
            min(l2, mid), min(r2, mid - 1), step - 1));
    res = max(res,
        dfs(min(l1, mid), min(r1, mid - 1),
            max(l2, mid + 1) - mid, max(r2, mid) - mid, step - 1));
    res = max(res,
        dfs(max(l1, mid + 1) - mid, max(r1, mid) - mid,
            min(l2, mid), min(r2, mid - 1), step - 1));
    res = max(res,
        dfs(max(l1, mid + 1) - mid, max(r1, mid) - mid,
            max(l2, mid + 1) - mid, max(r2, mid) - mid, step - 1));
    return res;
}


int main() {
    fast;
    int l1, l2, r1, r2; cin >> l1 >> r1 >> l2 >> r2;
    cout << dfs(l1, r1, l2, r2) << '\n';
    return 0;
}