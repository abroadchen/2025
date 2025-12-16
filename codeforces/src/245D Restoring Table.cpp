//
// Created by Psy.C on 2025/12/16.
//
/*
 *
*对每个节点i计算其对应的a[i]值：
第一个内层循环：j从i+1到n，将b[i][j]与a[i]进行OR运算
第二个内层循环：j从1到i-1，将b[j][i]与a[i]进行OR运算
这实际上是在计算第i行和第i列所有元素的按位OR值（除了对角线元素b[i][i]）
 *
*外层循环：O(n)
内层循环：O(n)
总体复杂度：O(n²)
对于n≤110的情况，这是完全可以接受的复杂度
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int b[N][N];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        cin >> b[i][j];
    }
    int a[N] = {};
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) a[i] |= b[i][j];
        for (int j = 1; j < i; ++j) a[i] |= b[j][i];
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}