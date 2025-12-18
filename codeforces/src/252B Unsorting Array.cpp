//
// Created by Psy.C on 2025/12/17.
//
/*
 *如果数组长度小于等于2，无法通过交换相邻元素得到不同的排列，输出"-1"
 *对数组b排序，得到递增序列，作为标准比较模板
*遍历相邻元素对（i和i+1）
如果相邻两元素相等，跳过（因为交换相等元素不会改变数组）
 *尝试交换第i个和第(i+1)个元素
*检查交换后的数组是否为递增序列
如果是递增序列（j==n），则恢复原状并继续尝试下一组
*检查交换后的数组是否为递减序列
b[n-j-1]是b数组的逆序访问（最大的元素到最小的元素）
如果是递减序列（j==n），则恢复原状并继续尝试下一组
*如果既不是递增也不是递减，则找到了符合条件的交换
输出交换的位置（1-indexed），程序结束
 *如果遍历完所有相邻对都没找到合适的交换，输出"-1"
 *
*时间复杂度：O(n²)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int n, i, j; cin>>n;
    int a[N], b[N];
    for (i = 0; i < n; ++i) cin>>a[i], b[i] = a[i];
    if (n <= 2) { cout << "-1"; return 0; }
    sort(b, b + n);
    for (i = 0; i < n - 1; ++i) {
        if (a[i] == a[i + 1]) continue;
        swap(a[i], a[i + 1]);
        for (j = 0; j < n && a[j] == b[j]; ++j) {}
        if (j == n) { swap(a[i], a[i + 1]); continue; }
        for (j = 0; j < n && a[j] == b[n - j - 1]; ++j) {}
        if (j == n) { swap(a[i], a[i + 1]); continue; }
        cout << i + 1 << ' ' << i + 2 << '\n';
        return 0;
    }
    cout << "-1";
    return 0;
}