//
// Created by Psy.C on 2025/12/8.
//
/*
*a: 存储输入数据
inv: 存储模逆元
c: 存储组合数相关值
 *
*对于每个i，计算C(k+i-1, i)的值
使用公式：C(n,k) = n!/(k!(n-k)!)，这里通过连续乘法实现
cur从k+i-1开始递减，inv[j]是j的模逆元
 *
*如果k不为0，则执行变换：
对每个位置i，计算从位置j到i的加权和，权重为c[i-j]
将结果存储在b数组中，然后复制回a数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2100
#define mod 1000000007
using namespace std;

int n, k;
int a[N], inv[N], c[N];

void init() {
    constexpr int p = mod; inv[1] = 1;
    for (int i = 2; i < N; ++i)
        inv[i] = static_cast<int>((p - p / i) * 1ll * inv[p % i] % p);
    c[0] = 1;
    for (int i = 1; i <= n; ++i) {
        c[i] = 1;
        int cur = k + i - 1;
        for (int j = 1; j <= i; ++j) {
            c[i] = static_cast<int>(1ll * c[i] * cur % p * inv[j] % p);
            --cur;
        }
    }
}

int b[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i]; init();
    if (k) {
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= i; ++j) {
            b[i] = static_cast<int>((b[i] + 1ll * a[j] * c[i - j]) % mod);
        }
        for (int i = 1; i <= n; ++i) a[i] = b[i];
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i==n];//最后一个元素后输出换行符，其余输出空格
    return 0;
}