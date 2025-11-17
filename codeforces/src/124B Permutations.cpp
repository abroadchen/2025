//
// Created by Psy.C on 2025/11/17.
//
/*
*读取n（数字个数）和k（每个数字的位数）
创建包含n个字符串的向量a
读取n个长度为k的数字字符串
*创建向量p存储0到k-1的排列
初始排列为[0, 1, 2, ..., k-1]
 *
*初始化最小差值mn为最大整数值
开始枚举所有可能的排列
*对于当前排列p，重新构造每个数字：
对每个原始数字字符串a[i]
按照排列p的顺序重新排列其数字位
将重新排列后的字符转换为整数num
将所有重构的数字存储在nums向量中
*对重构后的数字进行排序
计算最大值与最小值的差x
如果这个差值小于当前最小差值mn，则更新mn
继续下一个排列，直到所有排列都枚举完毕
 *
*排列数：k!
每次排列处理：O(n×k + n×log n)
总时间复杂度：O(k! × (n×k + n×log n))
 *适用于k较小的情况
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k; cin >> n >> k;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> p(k);
    for (int i = 0; i < k; ++i) p[i] = i;
    int mn = INT_MAX;
    do {
        vector<int> nums;
        for (int i = 0; i < n; ++i) {
            int num = 0;
            for (int j = 0; j < k; ++j) {
                num = num * 10 + a[i][p[j]] - '0';
            }
            nums.push_back(num);
        }
        sort(nums.begin(), nums.end());
        int x = nums.back() - nums.front();
        if (x < mn) mn = x;
    } while (next_permutation(p.begin(), p.end()));
    cout << mn << '\n';
    return 0;
}