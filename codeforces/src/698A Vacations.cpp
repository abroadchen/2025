//
// Created by Psy.C on 2026/4/17.
//
/**
n: 序列长度
a[i]: 第i个位置的原始值
f[i][j]: 到第i个位置为止，第i个位置状态为j时的最小操作次数
a[i] = 0: 位置i只能是0
a[i] = 1: 位置i可以是0或2（不能是1）
a[i] = 2: 位置i可以是0或1（不能是2）
a[i] = 3: 位置i可以是0、1或2
相邻两个位置不能同时为1
相邻两个位置不能同时为2
每个位置的值受a[i]限制
时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define mn(x,y,z) min(x,min(y,z))
using namespace std;
constexpr int N = 105;
int n, a[N], f[N][3];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(f, 0x3f, sizeof f);
    f[0][0] = f[0][1] = f[0][2] = 0;//边界条件
    for (int i = 1; i <= n; ++i) {
        //无论如何都可以改变当前位置为0，代价+1
        f[i][0] = mn(f[i-1][0], f[i-1][1], f[i-1][2]) + 1;
        //根据a[i]的值决定是否允许当前位置为2
        if (a[i] == 1 || a[i] == 3)//当前位置可以是2
            f[i][2] = min(f[i-1][0], f[i-1][1]);//2不能与前一个2相邻
        if (a[i] == 2 || a[i] == 3)//当前位置可以是1
            f[i][1] = min(f[i-1][0], f[i-1][2]);
    }
    ///取最后位置三种状态的最小值
    cout << mn(f[n][0], f[n][1], f[n][2]) << '\n';
    return 0;
}