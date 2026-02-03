//
// Created by Psy.C on 2026/2/3.
//
/**
* N：数组大小上限（200万）
a[N]：原数组
b[N]：辅助数组，用于归并操作
cnt[22][2]：计数数组，cnt[dep][0] 和 cnt[dep][1] 分别记录不同情况的数量
 *
 *区间只有一个元素时返回
*i：右半部分起始位置
j：左半部分起始位置
pos：结果数组的写入位置
 *分别处理左半部分和右半部分，深度减1
*外层循环：遍历右半部分的元素
内层循环1：当左半部分元素小于右半部分当前元素时，将其复制到辅助数组
cnt[dep][1] += j - l;：统计左边比当前右边元素小的数量
*内层循环2：处理左右两边相等的元素
cnt[dep][0] += mid - j + 1;：统计左边比当前右边元素大的数量 逆序对
b[pos++] = a[i++];：将右边元素加入辅助数组
*处理剩余元素：将左半部分剩余元素加入辅助数组
回写数组：将排序后的辅助数组内容复制回原数组
 *
 *时间复杂度：O((2^n) log(2^n) + m×n)，其中归并排序部分是 O(N log N)，查询部分是 O(m×n)
 *
*预处理阶段：通过DFS计算所有层级的原始逆序/正序对数
查询阶段：通过交换操作模拟翻转，无需真正翻转数组
结果计算：统计翻转后总的逆序对数量
*q 参数：表示要翻转的深度级别（从深度q到深度1）
交换效果：
原来 cnt[dep][0]（逆序对数）↔ cnt[dep][1]（正序对数）
模拟了数组翻转后，逆序对和正序对的互换
 *
*原数组：[a1, a2, a3, ..., an]
翻转后：[an, ..., a3, a2, a1]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e6;

int a[N], b[N], cnt[22][2];
inline void dfs(const int l, const int r, const int dep) {
    if (l == r) return;
    const int mid = (l + r) >> 1;
    int i = mid+1, j = l, pos = l;
    dfs(l, mid, dep-1), dfs(mid+1, r, dep-1);
    while (i <= r) {
        while (j <= mid && a[j] < a[i]) b[pos++] = a[j++];
        cnt[dep][1] += j - l;
        while (j <= mid && a[j] == a[i]) b[pos++] = a[j++];
        cnt[dep][0] += mid - j + 1;
        b[pos++] = a[i++];
    }
    while (j <= mid) b[pos++] = a[j++];
    for (i = l; i <= r; ++i) a[i] = b[i];
}


signed main() {
    fast;
    int n, i; cin >> n;
    for (i = 1; i <= 1<<n; ++i) cin >> a[i]; dfs(1, 1<<n, n);
    int m, q; cin >> m;
    while (m--) {
        cin >> q;
        while (q) swap(cnt[q][0], cnt[q][1]), q--;
        int res = 0;
        for (i = 1; i <= n; ++i) res += cnt[i][0];
        cout << res << '\n';
    }
    return 0;
}