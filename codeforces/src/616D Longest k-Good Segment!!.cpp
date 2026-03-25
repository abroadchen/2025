//
// Created by Psy.C on 2026/3/25.
//
/**
n为数组长度，k为最多不同元素个数，a为输入数组，num为计数数组
num数组大小为2*N是为了处理a[i]可能为负数的情况（如果a[i]可能为负，会加上偏移量映射到正数范围）
al, ar: 记录最长子数组的左右端点
l, r: 滑动窗口的左右端点
cnt: 当前窗口内不同元素的个数
O(n)，每个元素最多被访问两次（进入窗口和离开窗口）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;
int n, k, a[N], num[N<<1];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int al = 1, ar = k, l = 1, r = 0, cnt = 0;
    while (r < n) {//右端点还没到达数组末尾
        r++;//扩展右端点
        if (num[a[r]] == 0) cnt++;//该元素之前没出现过，不同元素个数加1
        num[a[r]]++;//该元素计数加1
        //不同元素个数超过k，收缩左端点
        while (cnt > k) {
            num[a[l]]--;//左端点元素计数减1
            if (num[a[l]] == 0) cnt--;//该元素计数变为0，不同元素个数减1
            l++;//收缩左端点
        }
        //当前窗口长度大于之前记录的最大长度
        if (r - l > ar - al) {
            ar = r; al = l;//更新最长子数组的左右端点
        }
    }
    cout << al << ' ' << ar;//输出最长子数组的左右端点（1-indexed）
    return 0;
}