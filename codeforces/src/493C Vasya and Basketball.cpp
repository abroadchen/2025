//
// Created by Psy.C on 2026/2/19.
//
/**
j:指向b数组末尾，t1,t2:最优解

从a数组最大元素开始（i = n-1）
找到b数组中所有大于等于a[i]的元素（从大到小）
x: 当前使用的a数组元素数量
y: 被a数组当前部分覆盖的b数组元素数量
目标是最大化 x - y（即净胜数量）

排序：O(n log n + m log m)
主循环：O(n + m)（双指针保证线性时间）
总体：O(n log n + m log m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1;
int n, a[N], m, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> b[i];
    sort(a, a + n);
    sort(b, b + m);
    int j = m-1, t1 = n, t2 = m;
    for (int i = n-1, x = 0, y = 0; i >= 0; --i) {
        while (j >= 0 && a[i] <= b[j]) {
            j--;
            y++;//计数被a[i]覆盖的b元素
        }
        x++;//计数当前a元素
        if (x - y >= t1 - t2) { t1 = x; t2 = y; }//更新最优解
    }
    if (t1 < t2) t1 = t2 = 0;//负数
    cout << n*2+t1 << ':' << m*2+t2 << '\n';
    return 0;
}