//
// Created by Psy.C on 2025/12/22.
//
/*
*++tot：先将tot自增1，然后作为数组下标
d[++tot] = i：将因子i存入数组
d[++tot] = n / i：将对应的另一个因子n/i存入数组
*i * i == n：如果i是n的平方根（即n是完全平方数）
d[++tot] = i：将平方根因子存入数组一次即可
 *
*n：元素个数
m：上限值
x：临时变量，用于读取数组元素
 *d[i] * 2^k 且 <= m
 *
 *初始值	序列 (m=100)
*d[i]=1	1, 2, 4, 8, 16, 32, 64
d[i]=3	3, 6, 12, 24, 48, 96
d[i]=5	5, 10, 20, 40, 80
d[i]=7	7, 14, 28, 56
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2020
using namespace std;

int d[N], tot;
void get(const int n) {
    int i;
    for (i = 1; i * i < n; ++i) if (n % i == 0) {//i是n的因子
        d[++tot] = i; d[++tot] = n / i;//d数组从索引1开始使用
    }
    if (i * i  == n) d[++tot] = i;
}


int main() {
    fast;
    int n, m, x; cin >> n >> m;
    cin >> x;
    int gcd = x - 1;
    for (int i = 2; i <= n; ++i) {
        cin >> x;
        gcd = __gcd(gcd, x - 1);//更新gcd为新的值
    }
    get(gcd);//获取gcd的所有因子并存储在数组d中
    ll ans = 0;
    for (int i = 1; i <= tot; ++i) if (d[i] & 1) {
        for (int j = d[i]; j <= m; j <<= 1) ans += m - j;//从j到m中有多少个数
    }
    cout << ans << '\n';
    return 0;
}