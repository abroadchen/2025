//
// Created by Psy.C on 2025/9/19.
//
/*
*动态分配布尔数组primes，用于埃拉托斯特尼筛法找质数
初始化：0和1不是质数，2到n初始标记为可能是质数(1)
使用埃拉托斯特尼筛法筛选质数：
从2开始到√n
如果i是质数，则将i的所有倍数标记为非质数
从2*i开始，每次增加i
 *
*创建向量primesVector存储所有找到的质数
遍历筛法结果，将质数加入向量
 *
 *
*初始化almostPrimeCount计数器
对每个数字i从2到n：
计算i的不同质因数个数divisors
遍历所有质数，如果质数能整除i，则divisors加1
如果divisors等于2，说明i恰好有2个不同质因数，是Almost Prime数
 *
 *
 *
 *时间复杂度：O(n log log n + n × π(n))，其中π(n)是不超过n的质数个数
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

int main() {

    int n(0); scanf("%d\n",&n);
    bool *primes = new bool[n+1]; primes[0] = 0; primes[1] = 0;

    for (int i = 2; i <= n; ++i) primes[i] = 1;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (!primes[i]) continue;
        for (int j = 2 * i; j <= n; j += i) primes[j] = 0;
    }

    vector<int> primesVector;
    for (int i = 2; i <= n; ++i) {
        if (primes[i])
            primesVector.push_back(i);
    }

    int almostPrimeCount(0);
    for (int i = 2; i <= n; ++i) {
        int divisors(0);
        for (int j = 0; j < primesVector.size(); ++j) {
            if (i % primesVector[j] == 0)
                ++divisors;
        }
        if (divisors == 2) ++almostPrimeCount;
    }

    printf("%d\n", almostPrimeCount);

    return 0;
}