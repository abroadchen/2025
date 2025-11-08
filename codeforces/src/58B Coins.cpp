//
// Created by Psy.C on 2025/10/23.
//

#include <cstdio>
#include <cmath>
using namespace std;

int main() {

    long n(0); scanf("%ld", &n);
    bool *primes = new bool[n + 1];
    primes[0] = primes[1] = 0;//将0和1标记为非质数(0表示不是质数)
    for (long i = 2; i <= n; ++i) primes[i] = 1;//假设从2到n的所有数字都是质数(1表示是质数)

    for (long i = 2; i <= sqrt(n); ++i) {
        if (!primes[i]) continue;//如果当前数字 i 已被标记为非质数，则跳过
        for (int j = 2 * i; j <= n; j += i) primes[j] = 0;//将当前质数 i 的所有倍数标记为非质数(这是埃拉托斯特尼筛法的核心)
    }

    long k(2), cur(n); printf("%ld ", cur);
    while (cur > 1 && k <= n) {
        if (!primes[k]) { ++k; continue; }
        if (cur % k == 0) {
            cur /= k;
            printf("%ld ", cur);
        } else ++k;
    }
    printf("\n");
    return 0;
}