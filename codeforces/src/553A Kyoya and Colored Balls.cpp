//
// Created by Psy.C on 2026/3/10.
//
/**
n: 累计变量，随输入动态变化
k: 输入的数据组数
c[N][N]: 二维数组，存储预计算的组合数（杨辉三角）
使用杨辉三角公式预计算所有组合数 C(i,j)
c[i][0] = 1: 每行第一个元素都是1（C(i,0) = 1）
c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod: 杨辉三角递推公式
即 C(i,j) = C(i-1,j) + C(i-1,j-1)，同时对模数取模

循环读入k个数值
cin >> x: 读入当前数值
ans *= c[x + n - 1][n]: 将当前组合数乘入答案
n += x: 更新n的值（累加x）
ans %= mod: 对答案取模，防止溢出

时间复杂度: O(N² + k)，其中N²用于预计算组合数，k用于主循环
空间复杂度: O(N²)，用于存储组合数表
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1001, mod = 1e9+7;
int n, k, c[N][N];
int main() {
    fast;
    for (int i = 0; i <= N-1; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    }
    cin >> k;
    ll ans = 1;
    for (int i = 1, x; i <= k; ++i) {
        cin >> x;
        ans *= c[x + n - 1][n];
        n += x;
        ans %= mod;
    }
    cout << ans << '\n';
    return 0;
}