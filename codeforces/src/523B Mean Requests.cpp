//
// Created by Psy.C on 2026/3/1.
//
/**
n：数组长度
T：滑动窗口大小
c：缩放因子
m：查询次数
p：当前查询的位置
i：用于遍历数组的索引
sum：滑动窗口的整数和（64位整型）
mean：经过缩放处理的平均值
j：查询循环的索引

sum += ans[i]：将当前元素加入窗口
if(i > T) sum -= ans[i - T]：如果窗口超过T个元素，移除最老的元素
(double)ans[i] / T：当前元素除以窗口大小
mean + ...：累加到mean
/ c：除以缩放因子c
real：真实的滑动窗口平均值
mean：经过特殊处理的平均值
(double)fabs(mean - real) / real：相对误差
 */
#include "bits/stdc++.h"
using namespace std;
int n, T;
double c;
int ans[200010];

int m, p;

int main()
{
    scanf("%d%d%lf", &n, &T, &c);
    int i;
    for(i = 1; i <= n; ++i) {
        scanf("%d", &ans[i]);
    }
    scanf("%d", &m);
    i = 1;
    __int64 sum = 0;
    double mean = 0;
    int j;
    for(j = 1; j <= m; ++j) {
        scanf("%d", &p);
        for( ; i <= p; ++i) {
            sum += ans[i];
            if(i > T)
                sum -= ans[i - T];
            mean = (mean + (double)ans[i] / T) / c;
        }
        double real = (double)sum / T;
        printf("%f %f %f\n", real, mean, (double)fabs(mean - real) / real);
    }
}