//
// Created by Psy.C on 2025/11/27.
//
/*
*创建大小为n的向量a，用于存储学生的综合评分
s: 学生的某个属性（可能是成绩、分数等）
p: 学生的另一个属性（可能是惩罚、扣分等）
计算综合评分：N * s - p
N * s：将s放大100倍，使其成为主要权重
- p：减去p值，作为次要因素
 *
*获取第k大的元素值
由于数组已升序排序，a[n-k]就是第k大的元素
 *
*计数：统计等于第k大元素值的元素个数
这是因为可能存在多个学生具有相同的综合评分
 *
 *时间复杂度：O(n log n)（主要是排序的复杂度） 空间复杂度：O(n)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 100;

int main() {
    fast;
    int n, k; cin >> n >> k;
    vector<int> a(n);
    int s, p;
    for (int i = 0; i < n; ++i) {
        cin >> s >> p;
        a[i] = N * s - p;
    }
    sort(a.begin(), a.end());
    const int x = a[n - k];
    int res = 0;
    for (int i = 0; i < n; ++i) if (a[i] == x) ++res;
    cout << res << '\n';
    return 0;
}