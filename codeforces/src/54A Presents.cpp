//
// Created by Psy.C on 2025/10/16.
//
/*
*计算覆盖last到x这段区间需要多少个组。
将这个数量加到总计数cnt中。
公式1 + (cur - 1) / k计算出覆盖cur个元素所需的最少组数，每组最多包含k个元素。
更新last为当前位置x，为下一次迭代做准备。
 *将从last到n这段剩余区间的完整组数加到总数量中
 *
 */
#include <cstdio>
using namespace std;

int main() {
    long n, k; scanf("%ld %ld", &n, &k);
    long c; scanf("%ld", &c);
    long last(0), cnt(0);
    for (long i = 0; i < c; ++i) {
        long x; scanf("%ld", &x);
        long cur = x - last;
        cnt += 1 + (cur - 1) / k;
        last = x;
    }
    cnt += (n - last) / k;
    printf("%ld\n", cnt);
    return 0;
}