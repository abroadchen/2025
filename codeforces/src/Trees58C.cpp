//
// Created by Psy.C on 2025/10/23.
//
/*
 *创建一个哈希表mp，用于存储键值对
 *
*i + 1: 从位置i到数组开头的元素个数
n - i: 从位置i到数组末尾的元素个数
shape: 取两者的较小值，表示以位置i为中心能形成的最长阶梯的长度
base: 计算这个阶梯形状的基准值（最小值），即a[i]减去阶梯高度差(shape-1)
 *如果基准值大于等于1，则在哈希表中将该基准值的计数加1
 *遍历哈希表，找到出现次数最多的基准值的出现次数，存入ans
 *输出结果：总元素个数n减去最多重复次数ans
 */
#include <vector>
#include <ios>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];//循环读取n个整数存入向量a中
    unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int shape = min(i + 1, n - i), base = a[i] - (shape - 1);
        if (base >= 1) mp[base]++;
    }

    int ans(0);
    for (auto& p : mp) ans = max(ans, p.second);
    cout << n - ans << '\n';
    return 0;
}