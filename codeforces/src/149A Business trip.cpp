//
// Created by Psy.C on 2025/11/22.
//
/*
 *贪心策略：从收入最高的月份开始选择
 *当累计收入未达到目标且还有月份可选时继续
 *
*排序：O(N log N) = O(12 log 12) = O(1)
贪心选择：O(N) = O(12) = O(1)
总体：O(1)（因为N是常数12）
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 12;

int main() {
    int lb; scanf("%d\n", &lb);//目标金额
    unsigned r[N] = {};//存储12个月的收入
    for (int i = 0; i < N; ++i) scanf("%d", r + i);//读取12个月的收入数据
    sort(r, r + N);
    int t(0), ans(0);//t: 累计收入总额 ans: 需要的月份数
    while (t < lb && ans < N) {
        ans++;//增加选择的月份数
        t += r[N-ans];//加上当前选择月份的收入（从后往前选）
    }
    if (t < lb) ans = -1;//如果累计收入仍未达到目标
    printf("%d\n", ans);
    return 0;
}