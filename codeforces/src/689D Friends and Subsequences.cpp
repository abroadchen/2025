//
// Created by Psy.C on 2026/4/15.
//
/**
f1：存储最大值的ST表
f2：存储最小值的ST表

ST表查询：O(1)时间查询区间最值
k计算：找到最大的2^k ≤ r-l+1
区间分割：将区间[l,r]分割为两个可能重叠的子区间
ql函数：找到从位置i开始，第一个最大值等于最小值的位置
qr函数：找到从位置i开始，最后一个最大值等于最小值的位置

输入：读取数组长度和两个数组
ST表预处理：O(n log n)时间构建
状态转移：f[i][j]表示从i开始2^j个元素的最值
遍历起点：对每个位置i，找到满足条件的区间
边界检查：确保找到有效的边界
结果累加：统计所有满足max = min的区间个数
预处理：O(n log n)
查询：O(n log n)
总体：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5, M = 30;

int f1[N][M], f2[N][M];
int qmax(int l, int r) {
    if (l == r) return f1[l][0];
    int k = log2(r - l + 1);
    return max(f1[l][k], f1[r-(1<<k)+1][k]);
}
int qmin(int l, int r) {
    if (l == r) return f2[l][0];
    int k = log2(r - l + 1);
    return min(f2[l][k], f2[r-(1<<k)+1][k]);
}

int n;
int ql(int i) {
    int l = i, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (qmax(i, mid) < qmin(i, mid)) l = mid + 1;
        else r = mid - 1;
    }
    if (l <= n && qmax(i, l) == qmin(i, l)) return l;
    return 0;
}
int qr(int i) {
    int l = i, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (qmax(i, mid) > qmin(i, mid)) r = mid - 1;
        else l = mid + 1;
    }
    if (r > 0 && qmax(i, r) == qmin(i, r)) return r;
    return 0;
}

int sum;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> f1[i][0];
    for (int i = 1; i <= n; ++i) cin >> f2[i][0];
    for (int j = 1; j <= 21; ++j)
        for (int i = 1; i+(1<<j)-1 <= n; ++i)
            f1[i][j] = max(f1[i][j-1], f1[i+(1<<(j-1))][j-1]);
    for (int j = 1; j <= 21; ++j)
        for (int i = 1; i+(1<<j)-1 <= n; ++i)
            f2[i][j] = min(f2[i][j-1], f2[i+(1<<(j-1))][j-1]);
    for (int i = 1; i <= n; ++i) {
        int l = ql(i), r = qr(i);
        if (l == 0) continue;
        if (r == 0) continue;
        if (l > r) swap(l, r);
        sum += r - l + 1;
    }
    cout << sum;
    return 0;
}