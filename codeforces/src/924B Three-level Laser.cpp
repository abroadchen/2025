//
// Created by Psy.C on 2026/10/14.
//
/**
目标：在 (a[i] , a[i]+k] 范围内找最靠右的下标（值最大的那个合法下标）。
左边界 l = i+2：保证三元组至少 i、i+1、l 三个不同下标（i+1 为中间点，l 从 i+2 开始）。
右边界 r = n。
经典"找 ≤ x 的最大下标"二分：mid=(l+r+1)>>1 向上取整，a[mid]<=x 时 l=mid，否则 r=mid-1。
最后若 a[l] ≤ x 返回 l（最右合法右端点），否则返回 -1（说明 a[i+2] > a[i]+k，无合法右端点）

分子 a[x]-a[i+1] 随 x 增大而增大。
分母 a[x]-a[i] 也随 x 增大而增大，但增长更快（因为 a[i] < a[i+1]，即 a[i+1] 比 a[i] 大，所以分子增长慢于分母）。
关键分析：设 f(x) = (x - b)/(x - a)（其中 a=a[i], b=a[i+1], a<b）。

f'(x) = [(x-a) - (x-b)] / (x-a)^2 = (b-a) / (x-a)^2 > 0
导数为正 → f(x) 随 x 单调递增。所以"取值最大的合法 x"必然给出最大比值。因此二分取最右合法 x 就是这一 i 的最优解——算法正确性正来源于此单调性

对每个左端点 i（i 从 1 到 n-2），调用 find(i) 得到最优右端点 x。
若无合法右端点（返回 -1）则跳过。
否则用该 x 计算比值 (a[x]-a[i+1])/(a[x]-a[i])，更新全局最大值 res
res 初始化为 -1。
若全程没有任何合法三元组（所有 find 都返回 -1），res 保持 -1 → 输出 -1。
否则输出最大比值，保留 10 位小数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10;

int a[N], k, n;
int find(int i) {
    int x = a[i] + k, l = i + 2, r = n;
    while (l < r) {
        int mid = (l+r+1)>>1;
        if (a[mid] <= x) l = mid;
        else r = mid-1;
    }
    if (a[l] <= x) return l;
    return -1;
}

double res = -1;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n-2; ++i) {
        int x = find(i);
        if (x == -1) continue;
        res = max(res, 1.*(a[x]-a[i+1])/(a[x]-a[i]));
    }
    if (res < 0) cout << "-1\n"; else cout << fixed << setprecision(10) << res;
    return 0;
}