//
// Created by Psy.C on 2025/12/1.
//
/*
*对于第i个输入的数字x，将a[x]设置为i
这建立了值到位置的映射关系
 *
*对于每个输入的数字x，输出a[x]（即该数字在第一次输入中的位置）
实现了查询每个数字在第一次输入中位置的功能
 *
* 时间复杂度：O(n) - 两次线性扫描
空间复杂度：O(n) - 存储映射数组
查询时间：O(1) - 每次查询都是直接数组访问
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int n, a[N];

int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) { cin >> x; a[x] = i; }
    for (int i = 1, x; i <= n; ++i) { cin >> x; cout << a[x] << " "; }
    return 0;
}