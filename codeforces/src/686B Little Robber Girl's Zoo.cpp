//
// Created by Psy.C on 2026/4/15.
//
/**
外层循环：i从1到n，表示排序轮数
内层循环：j从1到n-i，每轮减少一个比较，因为最大元素已经"冒泡"到正确位置
比较和交换：
如果a[j] > a[j+1]（相邻元素逆序），则需要交换
输出交换位置：输出需要交换的两个元素的位置j和j+1
执行交换：使用临时变量t完成a[j]和a[j+1]的交换

最坏情况：O(n²)，当数组完全逆序时
最好情况：O(n²)，即使数组已排序也要执行所有比较
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n;
int main() {
    fast;
    cin >> n;
    int a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n-i; ++j) {
            if (a[j] > a[j+1]) {
                cout << j << ' ' << j+1 << '\n';
                int t = a[j+1]; a[j+1] = a[j]; a[j] = t;
            }
        }
    return 0;
}