//
// Created by Psy.C on 2026/3/5.
//
/**
n: 数组总长度
k: 已知元素个数
p: 元素值的上限
x: 所有元素的总和上限
y: 目标中位数
a[N]: 存储数组元素
l = x: 剩余可用的总和（初始为x）
读入前k个已知元素，并从总和限制中扣除

mid = (n + 1) / 2: 计算中位数位置（第mid小的元素是中位数）
pos: 在已知元素中，小于y的元素个数
如果pos >= mid：

说明已知元素中已经有足够多的元素≥y
不可能使y成为中位数，设置l = -1表示无解
否则：

cnt = mid - 1 - pos: 需要添加的小于y的元素个数
在前mid-1个位置放最小值1（确保y能成为中位数）
其余位置放y值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1;
int n, k, p, x, y, a[N];
int main() {
    fast;
    cin >> n >> k >> p >> x >> y;
    int l = x;
    for (int i = 1; i <= k; ++i)
        cin >> a[i], l -= a[i];
    sort(a + 1, a + k + 1);
    int mid = (n + 1) / 2, pos = lower_bound(a + 1, a + k + 1, y) - (a+1);
    if (pos >= mid) l = -1;
    else {
        int cnt = mid - 1 - pos;
        for (int i = k+1; i <= k+cnt && i <= n; ++i)
            a[i] = 1, l -= 1;
        for (int i = k+cnt+1; i <= n; ++i)
            a[i] = y, l -= y;
    }
    if (l < 0) cout << "-1\n";
    else {
        for (int i = k+1; i <= n; ++i) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}