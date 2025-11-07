//
// Created by Psy.C on 2025/11/7.
//
/*
*a, b: 区间范围[a, b]
k: 目标质数
res: 结果存储变量
 *
 *如果x等于2，返回true（2是质数）
*如果找到因子，说明不是质数，返回false
这里只需要检查到√x是因为如果x有大于√x的因子，必然有对应的小于√x的因子
 *如果没有找到因子，说明是质数，返回true
 *
 *递归函数f，计算在[1,x]范围内能被i整除且最小质因子为i的数的个数
 *如果x小于i，返回0（没有这样的数）
 *如果i不是质数，返回0（只有质数才能作为最小质因子）
 *计算[1,x]中能被i整除的数的个数：x/i 将x更新为这个值（后续递归使用）
 *如果x小于i，说明没有更小的质因子需要排除，直接返回1
*减去那些最小质因子小于i但能被i整除的数：
对于每个小于i的数j，减去f(x,j)的值
这样就只剩下最小质因子恰好为i的数
 *
 *如果k不是质数，直接输出0并结束（因为题目要求最小质因子为k，k必须是质数）
*f(b,k)：[1,b]中最小质因子为k的数的个数
f(a-1,k)：[1,a-1]中最小质因子为k的数的个数
相减得到[a,b]中最小质因子为k的数的个数
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
int a, b, k;
ll res;

bool prime(int x) {
    if (x == 2) return 1;
    for (int i = 2; i * i <= x; ++i) if (x % i == 0) return 0;
    return 1;
}

int f(int x, int i) {
    if (x < i) return 0;
    if (!prime(i)) return 0;
    int res = x / i; x = res;
    if (x < i) return 1;
    for (int j = 2; j < i; ++j) res -= f(x, j);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> a >> b >> k;
    if (!prime(k)) { cout << 0; return 0; }
    res = f(b, k) - f(a - 1, k);
    cout << res;
    return 0;
}