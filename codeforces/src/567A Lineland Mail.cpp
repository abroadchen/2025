//
// Created by Psy.C on 2026/3/12.
//
/**
mx[N]: 每个位置的最大距离
mn[N]: 每个位置的最小距离

计算元素a[i]到左边界l和右边界r的距离的最大值
abs(l - a[i]): 到左边界距离
abs(r - a[i]): 到右边界距离
计算元素a[i]与其左右相邻元素的距离的最小值
abs(a[i+1] - a[i]): 与右邻居距离
abs(a[i] - a[i-1]): 与左邻居距离
首元素(i == 0): 最小距离是到右邻居的距离
尾元素(i == n-1): 最小距离是到左邻居的距离
时间复杂度：O(n)
空间复杂度：O(n)
一次遍历完成所有计算
特殊处理边界情况
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5;
int n, a[N], mx[N], mn[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int l = a[0], r = a[n-1];
    for (int i = 0; i < n; ++i) {
        mx[i] = max(abs(l - a[i]), abs(r - a[i]));
        mn[i] = min(abs(a[i+1] - a[i]), abs(a[i] - a[i-1]));
        if (i == 0) mn[i] = abs(l - a[i+1]);
        else if (i == n-1) mn[i] = abs(r - a[i-1]);
        cout << mn[i] << ' ' << mx[i] << '\n';
    }
    return 0;
}