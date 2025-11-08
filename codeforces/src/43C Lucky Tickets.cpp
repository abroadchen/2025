//
// Created by Psy.C on 2025/9/26.
//
/*
 *\n读取并忽略输入末尾的换行符
 *
*z / 2：每两个余数为0的数可以组成一对（它们的和能被3整除）
o < t ? o : t：余数为1和余数为2的数配对，取较小值（每对1和2的组合和为3的倍数）
将两部分结果相加得到最大配对数
 *
 *
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {

    long n; scanf("%ld\n", &n);
    long z(0), o(0), t(0);

    while (n--) {
        long x; scanf("%ld", &x);
        if (x % 3 == 0) ++z;
        else if (x % 3 == 1) ++o;
        else if (x % 3 == 2) ++t;
    }

    long ans = (z / 2) + (o < t ? o : t);
    printf("%ld\n", ans);
    return 0;
}