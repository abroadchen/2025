//
// Created by Psy.C on 2026/1/12.
//
/**
* 没有找到大于等于x的元素
x比v中所有元素都大
将x添加到v的末尾（保持v有序）
 *
*找到了第一个大于等于x的位置
将该位置的值替换为x
it-v.begin() 将迭代器转换为索引
 *
 *v[i]表示长度为i+1的递增子序列的最小结尾元素
*当遇到比v中所有元素都大的数时，扩展序列长度
当遇到中间大小的数时，更新相应位置，使后续更容易扩展
 *
* O(n log n)，其中n是数组长度
每次操作使用二分查找：O(log n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> v;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (auto it = lower_bound(v.begin(), v.end(), x); it == v.end()) v.push_back(x);
        else v[it-v.begin()] = x;
    }
    cout << v.size() << '\n';
    return 0;
}