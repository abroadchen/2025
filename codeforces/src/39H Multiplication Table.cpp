//
// Created by Psy.C on 2025/9/24.
//
/*
*prod / k：商（高位数字）
prod % k：余数（低位数字）
组合成：商×10 + 余数
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {

    int k; scanf("%d",&k);

    for (long i = 1; i < k; ++i) {
        for (long j = 1; j < k; ++j) {
            long prod = i * j;
            if (prod >= k) prod = 10 * (prod / k) + prod % k;
            printf("%ld ", prod);
        }
        puts("");
    }
    return 0;
}