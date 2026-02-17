//
// Created by Psy.C on 2026/2/17.
//
/**
unique函数将相邻的重复元素移到数组末尾
返回去重后有效元素的末尾迭代器
减去起始地址得到新的数组长度

外层循环：for (int i = 0; i < n; ++i)
遍历数组中的每个元素作为基数f[i]
内层循环：for (int j = 2; j*f[i] <= f[n-1]+f[i]; ++j)
j = 2: 从2开始（因为1*f[i]=f[i]，对结果无意义）
j*f[i] <= f[n-1]+f[i]: 循环终止条件
j*f[i]: f[i]的j倍
f[n-1]: 数组中的最大值
条件确保j倍不会超出合理范围

lower_bound(f, f+n, f[i]*j): 在有序数组中找第一个≥f[i]*j的元素位置
lower_bound(...) - 1: 取前一个元素（即最大的<f[i]*j的元素）
t是数组中小于f[i]*j的最大值
即在f[i]*(j-1)到f[i]*j之间的最大数组元素

对于除法 a % b，最大余数接近 b-1
当 a 接近 b 的倍数时，余数最大

排序：O(n log n)
去重：O(n)
双重循环：O(n * (最大值/最小值) * log n)
总体：O(n² * log n)（在最坏情况下）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 200005;
int n, f[N];
void init() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> f[i];
    sort(f, f + n);
    n = unique(f, f + n) - f;
}

int get() {
    int res = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 2; j*f[i] <= f[n-1]+f[i]; ++j) {
            const int t = *(lower_bound(f, f+n, f[i]*j) - 1);
            res = max(res, t%f[i]);
        }
    return res;
}


int main() {
    fast; init();
    cout << get() << '\n';
    return 0;
}