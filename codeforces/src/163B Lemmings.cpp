//
// Created by Psy.C on 2025/11/27.
//
/*
*定义常量N = 100005（数组大小）
n: 元素总数
k: 需要选择的元素数量
h: 某个参数（高度或其他）
ans[N]: 存储答案的数组
*m: 某种属性（可能是质量mass）
v: 某种属性（可能是速度velocity）
pos: 原始位置
 *
*
读取每个节点的m和v值
记录原始位置
 *按自定义比较函数排序（从d[1]到d[n]）
 *
*搜索范围：[0, 1e9]
迭代100次确保精度
对于每个mid值，从后往前检查能满足条件的元素个数
如果能找到k个满足条件的元素，缩小右边界；否则缩小左边界
 *
*cnt <= 0：找到了≥k个元素
当前 mid 值可行
可以尝试更小的值（r = mid）
cnt > 0：找到<k个元素
当前 mid 值不可行
需要更大的值（l = mid）
 *
 *
 *
 *
*排序：O(n log n)
二分搜索：O(100 × n)
总体：O(n log n)
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;
int n, k, h, ans[N];
struct node {
    int m, v, pos;
    bool operator<(const node& rhs) const {
        if (m != rhs.m) return m < rhs.m;
        return v < rhs.v;
    }
} d[N];

int main() {
    fast;
    cin >> n >> k >> h;
    for (int i = 1; i <= n; ++i) { cin >> d[i].m; d[i].pos = i; }
    for (int i = 1; i <= n; ++i) cin >> d[i].v;
    sort(d + 1, d+1+n);
    double l(0), r(1e9);
    for (int i = 0; i < 100; ++i) {
        const double mid = (l + r) / 2.; int cnt = k;
        for (int j = n; j >= 1; --j) if (mid * d[j].v / h >= 1. * cnt) cnt--;
        if (cnt <= 0) r = mid;
        else l = mid;
    }
    int cnt = k;
    for (int j = n; j >= 1; --j) {
        if (r * d[j].v / h >= 1. * cnt) ans[cnt--] = d[j].pos;
        if (cnt == 0) break;
    }
    for (int i = 1; i <= k; ++i) cout << ans[i] << " ";
    return 0;
}