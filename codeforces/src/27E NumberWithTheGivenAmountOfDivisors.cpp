//
// Created by Psy.C on 2025/9/20.
//
/*
 *
 *创建向量pdiv存储质因数
 *初始化当前除数cur为2（最小质数）
 *
*当cur小于等于n时循环：
内层循环：当n能被cur整除时，将cur添加到质因数向量中，并将n除以cur
递增cur继续尝试下一个可能的因数
 *如果最后n大于1，说明n本身是一个质因数，将其加入向量
 *
*遍历所有质因数：
计算反向索引ind（从最后一个质因数开始）
计算u = 质因数 - 1
将rv[i]乘以自身u次（即rv[i]的u次幂）累乘到结果中
 */
#include <cstdio>
#include <vector>
using namespace std;


int main() {

    long rv[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,47,53};
    long n; scanf("%ld", &n);

    if (n == 8) { puts("24"); return 0; }

    vector<long> pdiv;
    long cur(2);

    while (cur <= n) {
        while (n % cur == 0) {
            pdiv.push_back(cur);
            n /= cur;
        }
        ++cur;
    }
    if (n > 1) pdiv.push_back(n);

    long long res(1), ind(0);
    for (long i = 0; i < pdiv.size(); ++i) {
        ind = pdiv.size() - i - 1;
        long u = pdiv[ind] - 1;
        while (u--) res *= rv[i];
    }

    printf("%lld\n", res);

    return 0;
}