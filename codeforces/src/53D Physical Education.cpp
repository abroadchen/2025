//
// Created by Psy.C on 2025/10/15.
//
/*
*创建两个大小为n+1的整型向量a和b（索引从0到n）
实际使用时从索引1开始，索引0未使用
 *创建pair<int,int>类型的向量p，用于存储交换操作的记录
 *
*从后往前遍历数组（从n到1）
这是一种贪心策略，先确定最后位置的元素
 *
*寻找在数组b中等于a[i]的元素位置j
从位置1开始向后搜索，直到找到匹配的元素
从位置j开始，逐步将元素向右移动到位置i
注意这里的j已经在前面找到了正确值的位置
将交换操作{j, j+1}记录到向量p中
表示交换位置j和j+1的元素
实际执行交换操作，将b[j]和b[j+1]交换
这样b[j]就向右移动了一位
输出总的交换操作次数
遍历所有记录的交换操作并输出
每行输出一对相邻位置的交换操作
 *
 *
 *
*从数组末尾开始，逐个位置进行处理
对于每个位置i，如果a[i] ≠ b[i]，则：
在数组b中找到等于a[i]的元素位置j
通过连续的相邻交换，将该元素从位置j移动到位置i
记录所有执行的交换操作
输出最少的交换步骤和具体操作
时间复杂度： O(n³) - 最坏情况下每个元素可能需要O(n²)的交换操作 空间复杂度： O(n) - 存储数组和交换记录
 *
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n; cin>>n;
    vector<int> a(n + 1), b(n + 1);
    vector<pair<int,int> > p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = n; i >= 1; --i) {
        if (a[i] == b[i]) continue;
        int j(1);
        while (b[j] != a[i]) j++;
        for (j; j < i; ++j) {
            p.push_back({j, j + 1});
            swap(b[j], b[j + 1]);
        }
    }
    cout << p.size() << '\n';
    for (auto x : p) cout << x.first << ' ' << x.second << '\n';
}



int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    solve();
    return 0;
}