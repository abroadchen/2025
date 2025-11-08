//
// Created by Psy.C on 2025/9/21.
//
// sum: 数组所有元素的和
// target: 当前子数组和（用于Kadane算法）
// maxsubsum: 最大子数组和

#include <cstdio>
using namespace std;

int main() {

    long n; scanf("%ld\n", &n);
    long sum(0), target(0), maxsubsum(0);

    while (n--) {// 逐个读取数组元素
        long a; scanf("%ld", &a);// 读取当前元素
        sum += a;
        target += a;

        if (target < 0) target = 0;// Kadane算法的核心：如果当前子数组和为负，重新开始
        if (target > maxsubsum) maxsubsum = target;// 更新最大子数组和
    }

    printf("%ld\n", 2 * maxsubsum - sum);

    return 0;
}