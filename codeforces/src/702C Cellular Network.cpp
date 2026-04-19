//
// Created by Psy.C on 2026/4/18.
//
/**
n: 数组a的长度
k: 数组b的长度
a[N]: 第一个数组
b[N]: 第二个数组（有序）
b[0] = b[1]: 将b[1]复制到b[0]，作为左边界
b[k+1] = b[k]: 将b[k]复制到b[k+1]，作为右边界
lower_bound(b + 1, b + 1 + k, a[i]): 在有序数组b中找到第一个大于等于a[i]的元素位置
- b: 将迭代器转换为数组索引
pos: 找到的位置索引
abs(a[i]-b[pos]): a[i]到b[pos]的距离
abs(a[i]-b[pos-1]): a[i]到b[pos-1]的距离
min(...): 取两者中的较小值（最短距离）
更新全局最大距离
O(n log k): 对每个a[i]进行一次二分查找
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, k, a[N], b[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= k; ++i) cin >> b[i];
    b[0] = b[1]; b[k+1] = b[k];
    int ans = 0;
    for (int i = 1, pos, dis; i <= n; ++i) {
        pos = lower_bound(b + 1, b + 1 + k, a[i]) - b;
        dis = min(abs(a[i]-b[pos]), abs(a[i]-b[pos-1]));
        ans = max(ans, dis);
    }
    cout << ans << '\n';
    return 0;
}