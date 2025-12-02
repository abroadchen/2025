//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 目标金额或目标值
a[N]: 存储3种面值的数组
f[M]: 动态规划数组，f[i]表示组成金额i所需的最大硬币数
 *初始化：组成金额0需要0个硬币
 *
*外层循环：遍历3种面值
内层循环：遍历金额从a[i]到n
如果f[j-a[i]]不可达（<0），则跳过
否则更新f[j]为当前值和通过使用面值a[i]得到的值的最大值
 *
*时间复杂度：O(3 × n) = O(n)
空间复杂度：O(M)
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 12, M = 120000;
int n, a[N], f[M];

int main() {
    fast;
    cin >> n >> a[1] >> a[2] >> a[3];
    memset(f, -1, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= 3; ++i) {
        for (int j = a[i]; j <= n; ++j) {
            if (f[j - a[i]] < 0) continue;
            f[j] = max(f[j], f[j - a[i]] + 1);
        }
    }
    cout << f[n];
    return 0;
}