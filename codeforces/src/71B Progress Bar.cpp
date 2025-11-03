//
// Created by Psy.C on 2025/11/3.
//
/*
*n: 总共的槽位数量
k: 每个槽位的最大容量
t: 填充百分比
f: 完全填满的槽位数量
p: 最后一个部分填充槽位的填充量
 *
*计算完全填满的槽位数f：n*t/100（整数除法自动向下取整）
计算部分填充的槽位中的填充量p：
n*t表示总的百分比单位
100*f表示完全填满部分占用的百分比单位
(nt - 100f)是剩余的百分比单位
乘以k再除以100得到实际填充量
 *
 *输出f个完全填满的槽位，每个槽位填充量为k
*如果不是所有槽位都完全填满（还有剩余槽位）：
输出部分填充槽位的填充量p
输出剩余的空槽位，数量为(n-f-1)，每个填充量为0
 *
 *
 */
#include <cstdio>
using namespace std;

int n, k, t, f, p;

int main() {
    scanf("%d %d %d", &n, &k, &t);
    f = n * t / 100;
    p = (n * t - 100 * f) * k / 100;
    for (int i = 0; i < f; ++i) printf("%d ", k);
    if (f < n) {
        printf("%d ", p);
        for (int i = 0; i < n - f - 1; ++i) printf("0 ");
    }
    puts("");
    return 0;
}