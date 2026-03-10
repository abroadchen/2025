//
// Created by Psy.C on 2026/3/10.
//
/**
a[N]: 存储最终排列结果的数组
f[N]: 存储斐波那契数列的数组

l, r: 当前处理区间的左右端点
x: 当前要找的排列序号（在当前区间内）
d = r - l + 1: 当前区间长度
递归终止条件：区间为空或只有一个元素
情况1 (x <= f[d]): 第x小的排列属于"较小"的那部分
设置 a[l] = l, a[l+1] = l+1（保持顺序）
递归处理剩余部分 [l+1, r]，序号仍为x
情况2 (x > f[d]): 第x小的排列属于"较大"的那部分
设置 a[l] = l+1, a[l+1] = l（交换顺序）
递归处理剩余部分 [l+2, r]，序号调整为 x - f[d]

n: 排列长度
k: 要找的排列序号
f[1]=1, f[2]=1
递推计算斐波那契数列到f[n]
f[i] = f[i-1] + f[i-2] 是斐波那契递推公式
从区间[1,n]开始，寻找第k小的排列
递归构建目标排列
时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 51;

int a[N], f[N];
void dfs(int l, int r, int x) {
    int d = r - l + 1;
    if (d == 0) return;
    if (d == 1) { a[l] = l; return; }
    if (x <= f[d]) {
        a[l] = l;
        a[l+1] = l + 1;
        dfs(l + 1, r, x);
    } else {
        a[l] = l + 1;
        a[l+1] = l;
        dfs(l + 2, r, x - f[d]);
    }
}

int n, k;
signed main() {
    fast;
    cin >> n >> k;
    f[1] = f[2] = 1;
    for (int i = 3; i <= n; ++i)
        f[i] = f[i-1] + f[i-2];
    dfs(1, n, k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}