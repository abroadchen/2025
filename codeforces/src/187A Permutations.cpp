//
// Created by Psy.C on 2025/12/2.
//
/*
*p[b] = i + 1：记录元素b在序列中的位置（从1开始计数）
这样p数组就建立了"元素值 → 在b中位置"的映射关系
 *
*寻找最长前缀，使得在序列b中的位置是递增的：
检查相邻元素在序列b中的位置关系
如果p[a[i]] < p[a[i-1]]，说明位置顺序被打乱，需要移动
从位置i开始，后面的元素都需要重新排列
 *计算需要移动的元素数量：总长度n减去保持顺序的前缀长度i
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 210000
using namespace std;

int a[N], p[N];

int main() {
    fast;
    int n; cin >> n; int i, b;
    for (i = 0; i < n; ++i) cin >> a[i];
    for (i = 0; i < n; ++i) { cin >> b; p[b] = i + 1; }
    for (i = 1; i < n; ++i) if (p[a[i]] < p[a[i-1]]) break;
    const int ans = n - i; cout << ans << '\n';
    return 0;
}