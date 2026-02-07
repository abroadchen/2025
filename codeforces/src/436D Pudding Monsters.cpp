//
// Created by Psy.C on 2026/2/7.
//
/**
读取n（数组长度）和m（另一个数组长度）
读取数组a并排序
设置边界哨兵值，确保边界处理的一致性

L[i]: a[i]所在连续序列的左边界索引
R[i]: a[i]所在连续序列的右边界索引
如果a[i]与前一个数连续，L[i]=L[i-1]；否则L[i]=i
从右往左遍历设置R数组

sum[x]: 小于等于x的数字在b数组中的出现次数
读取数组b并对每个值计数
对b数组排序
计算sum的前缀和

1. a[i] - b[l] 部分
a[i]: 当前处理的数组a中的元素
b[l]: 数组b中的某个元素（满足 b[l] <= a[i]）
a[i] - b[l]: 两者的差值，代表从位置i向前回溯的步数
2. i - (a[i] - b[l]) 部分
从当前位置i向前移动 (a[i] - b[l]) 步
得到一个新的索引位置：i - (a[i] - b[l])
这个位置满足：如果从该位置开始一个连续序列，到达位置i时数值正好从b[l]变化到a[i]
3. L[i-(a[i]-b[l])] 部分
L[] 数组记录每个位置所在连续序列的左边界
L[i-(a[i]-b[l])] 找到上述新位置所在连续序列的左边界
这样做是为了处理连续相同数字的情况
4. dp[L[i-(a[i]-b[l])]-1] 部分
获取连续序列左边界之前的状态值
L[i-(a[i]-b[l])]-1 是目标状态的索引
5. sum[a[i]]-sum[b[l]-1] 部分
使用前缀和计算区间 [b[l], a[i]] 内在数组b中出现的元素个数
sum[a[i]]: ≤ a[i] 的b数组元素个数
sum[b[l]-1]: ≤ (b[l]-1) 的b数组元素个数
相减得到 [b[l], a[i]] 区间内b数组元素个数

dp[L[i-(a[i]-b[l])]-1]: 之前状态的最优值
sum[a[i]]-sum[b[l]-1]: 本次操作获得的收益
总和构成新的可能解

第一行：更新当前dp[i]值
第二行：更新mx值，为后续计算做准备


1. i + b[r] - a[i] 部分
i: 当前处理的位置
a[i]: 位置i处的值
b[r]: 数组b中的某个元素（满足 b[r] >= a[i]）
b[r] - a[i]: 从a[i]到b[r]需要增加的数值
i + (b[r] - a[i]): 从位置i向前推进，按照数值递增的方式到达值为b[r]的位置
2. R[i+b[r]-a[i]] 部分
R[] 数组记录每个位置所在连续序列的右边界
R[i+b[r]-a[i]] 将目标位置映射到其所在连续序列的右边界
这样处理是为了统一处理连续相等元素的情况
3. mx + sum[b[r]] - sum[a[i]] 部分
mx: 前面计算得到的中间结果，表示在位置i处的最佳状态值
sum[b[r]]: ≤ b[r] 的b数组元素个数
sum[a[i]]: ≤ a[i] 的b数组元素个数
sum[b[r]] - sum[a[i]]: 区间 (a[i], b[r]] 内b数组元素的个数
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 200009, M = 2009;

int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N], i;
    rep(i,n) cin >> a[i];
    sort(a + 1, a + n + 1);
    a[0] = a[1] - 1000, a[n+1] = a[n] + 1000;
    int L[N], R[N];
    rep(i,n) {
        if (a[i] == a[i-1] + 1) L[i] = L[i-1];
        else L[i] = i;
    }
    for (i = n; i; --i) {
        if (a[i] == a[i+1] - 1) R[i] = R[i+1];
        else R[i] = i;
    }
    int sum[N], b[M]; sum[0] = 0;
    rep(i,m) cin >> b[i], sum[b[i]]++;
    sort(b + 1, b + m + 1);
    rep(i,200000) sum[i] += sum[i-1];
    int dp[N];
    rep(i,n) {
        dp[i] = max(dp[i], dp[i-1]);//继承前一个状态的最优解
        int mx;
        if (L[i] == i) mx = dp[i-1] + sum[a[i]] - sum[a[i]-1];//当前是连续段起点
        else mx = -10000000;//不是起点，设为极小值
        dp[i] = max(dp[i], mx);//更新
        for (int l = 1; b[l] <= a[i] && l <= m; ++l) {
            if (i - (a[i] - b[l]) >= 1) {
                dp[i] = max(dp[i], dp[L[i-(a[i]-b[l])]-1]+sum[a[i]]-sum[b[l]-1]);
                mx = max(mx, dp[L[i-(a[i]-b[l])]-1]+sum[a[i]]-sum[b[l]-1]);
            }
        }
        for (int r = m; b[r] >= a[i] && r; --r) {
            if (i + b[r] - a[i] <= n)
                dp[R[i+b[r]-a[i]]] = max(dp[R[i+b[r]-a[i]]], mx+sum[b[r]]-sum[a[i]]);
        }
    }
    cout << dp[n] << '\n';
    return 0;
}