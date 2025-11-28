//
// Created by Psy.C on 2025/11/28.
//
/*
*a: 起始数字
n: 数字个数
x[N]: 数组，用于存储处理后的数值
*初始化数组：将 x[a] 到 x[a+n-1] 设置为对应的数字值
即 x[i] = i for i in [a, a+n-1]
 *
*去除完全平方数因子
外层循环：遍历所有可能的平方数底数 i（从2开始）
p = i * i：当前的完全平方数
t = ((a + p - 1) / p) * p：找到从 a 开始第一个能被 p 整除的数
内层循环：从 t 开始，每隔 p 个数处理一次
while 循环：将 x[j] 中的所有 p 因子都除掉
 *计算处理后所有数的和
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 1e7+1;
int a, n, x[N];

int main() {
    fast;
    cin >> a >> n;
    for (int i = a; i <= a + n - 1; ++i) x[i] = i;
    for (int i = 2; i * i <= a + n - 1; ++i) {
        const int p = i * i, t = ((a + p - 1) / p) * p;
        for (int j = t; j <= a + n - 1; j += p) {
            while (x[j] % p == 0) x[j] /= p;
        }
    }
    ll ans = 0;
    for (int i = a; i <= a + n - 1; ++i) ans += x[i];
    cout << ans << '\n';
    return 0;
}