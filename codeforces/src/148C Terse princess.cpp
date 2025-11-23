//
// Created by Psy.C on 2025/11/22.
//
/*
 *n(数组长度)、a(需要增加的连续相等段数)、b(需要增加的递增段数)
 *cur: 当前元素的值  sum: 前缀和
 *
 *从第二个元素开始构造数组(索引1开始)
 * 如果还有递增段数需要增加(b > 0)
 *当前值设为前缀和+1，确保严格递增
 * 递增段数减1
 *如果不是前两个元素且还有连续相等段数需要增加(a > 0)
 *当前值比前一个元素大1，保持递增但增加相等段
 *连续相等段数减1
 *如果a和b都为0，则保持当前值不变(形成相等段)
 *设置当前元素值
 *更新前缀和
 *如果还有未使用的a或b，说明无法构造满足条件的数组
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    int n, a, b; scanf("%d %d %d", &n, &a, &b);
    vector<int> v(n, 1);
    int cur(1), sum(1);
    for (int i = 1; i < n; ++i) {
        if (b > 0) { cur = sum + 1; --b; }
        else if (i > 1 && a > 0) { ++cur; --a; }
        v[i] = cur;
        sum += cur;
    }
    if (a > 0 || b > 0) puts("-1");
    else {
        for (int i = 0; i < n; ++i) printf("%d ", v[i]);
        puts("");
    }
    return 0;
}