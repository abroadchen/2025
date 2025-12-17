//
// Created by Psy.C on 2025/12/16.
//
/*如果需要的组合数k不超过数组元素个数n：
输出k行，每行格式为"1 元素值"
 *
*输出每个单独元素的组合（每行格式为"1 元素值"）
每输出一个组合，计数器加1
 *
*外层循环i从1到n-1（表示额外选取的元素个数）
内层循环j从0到n-i-1（表示基础元素索引）
输出格式：先输出组合大小(i+1)，然后输出最大的i个元素，最后输出a[j]
每生成一个组合计数器加1
如果达到k个组合就结束程序
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2100
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int a[N];
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (k <= n) {
        for (int i = 0; i < k; ++i) cout << 1 << ' ' << a[i] << '\n';
        return 0;
    }
    sort(a, a + n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cout << 1 << ' ' << a[i] << '\n';
        cnt++;
    }
    for (int i = 1; i < n; ++i) for (int j = 0; j < n - i; ++j) {
        cout << i + 1 << ' ';
        for (int x = n - 1; x >= n - i; --x) cout << a[x] << ' ';
        cout << a[j] << '\n';
        cnt++;
        if (cnt == k) return 0;
    }
    return 0;
}