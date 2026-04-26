//
// Created by Psy.C on 2026/4/25.
//
/**
n：数组长度
a[N]：输入数组
q[N]：前缀和数组
f[2][2][N][N]：四维DP数组，使用滚动数组优化第一维
初始化状态：玩家0(先手)为负无穷，玩家1(后手)为正无穷

外层循环：从大到小枚举剩余步数
f[0/1][k&1][l][r]：当前轮到玩家0/1，还剩k步，左边已取l个，右边已取r个时的最优得分
k&1：奇偶性滚动数组优化
l：左边已经取走的元素数量
r：右边已经取走的元素数量
状态转移逻辑
玩家0（先手）：尝试最大化自己的优势
玩家1（后手）：尝试最小化对手的优势
从左边取k个：获得分数q[l] - q[l-k]
从右边取k个：损失分数q[n-r+k] - q[n-r]
输出游戏结束时先手玩家相对于后手玩家的优势

// k为奇数时：k&1=1, (k-1)&1=0
// k为偶数时：k&1=0, (k-1)&1=1
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 4e3+7, inf = 1e18;

int n, a[N], q[N], f[2][2][N][N];
signed main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], q[i] = q[i-1] + a[i];
    for (int l = 0; l <= n-100; ++l)
        for (int r = 0; r <= n-100-l; ++r)
            f[0][0][l][r] = -inf, f[1][0][l][r] = inf;
    for (int k = 100; k >= 1; --k) {
        for (int l = 0; l <= n-k+1; ++l)
            for (int r = max(0ll, l-100); r <= min(l+100, n-k-l+1); ++r)
                f[0][k-1&1][l][r] = -inf, f[1][k-1&1][l][r] = inf;
        for (int l = n; l >= 0; --l)
            for (int r = min(l+100, n-l); r >= max(0ll, l-100); --r) {
                if (f[0][k&1][l][r] != -inf && r >= k) {
                    f[1][k&1][l][r-k] = min(f[1][k&1][l][r-k], f[0][k&1][l][r] - q[n-r+k] + q[n-r]);
                    f[1][k-1&1][l][r-k] = min(f[1][k-1&1][l][r-k], f[0][k&1][l][r] - q[n-r+k] + q[n-r]);
                }
                if (f[1][k&1][l][r] != inf && l >= k) {
                    f[0][k&1][l-k][r] = max(f[0][k&1][l-k][r], f[1][k&1][l][r] + q[l] - q[l-k]);
                    f[0][k-1&1][l-k][r] = max(f[0][k-1&1][l-k][r], f[1][k&1][l][r] + q[l] - q[l-k]);
                }
            }
    }
    cout << f[0][1][0][0];
    return 0;
}