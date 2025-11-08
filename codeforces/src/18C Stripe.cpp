//
// Created by Psy.C on 2025/9/17.
//
/*
 *\n读取并丢弃换行符
 *
 *如果左侧和等于总和的一半，说明找到了一个满足条件的分割点，ways加1
 *将数组分割成两个非空的连续子数组，使得两个子数组的元素和相等
 *
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    long n; scanf("%ld\n", &n);
    vector<long long> numbers(n, 0);
    long long total(0), leftSum(0), ways(0);

    for (long k = 0; k < n; ++k) {
        scanf("%lld ", &numbers[k]);
        total += numbers[k];
    }
    for (long k = 0; k < n - 1; ++k) {
        leftSum += numbers[k];
        if (2 * leftSum == total) ++ways;
    }

    printf("%lld\n", ways);
    
    return 0;
}