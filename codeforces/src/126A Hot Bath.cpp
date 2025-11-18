//
// Created by Psy.C on 2025/11/17.
//
/*
*a, b：两个权重值
e：目标值
m = 1e8：当前最优解的加权平均值（初始化为很大值）
c, d：当前搜索的整数对
x, y：记录最优解的整数对
 *
 *c和d都不为-1（~c等价于c!=-1）
 *加权平均值：k = (a×c + b×d) / (c + d)
*如果当前加权平均值小于目标值
减少c值，继续下一次循环
*如果当前解比最优解更优（k更接近目标值e）
更新最优解：x=c, y=d, m=k
注意：这里应该是abs(k-e) < abs(m-e)更合理
 *减少d值，继续搜索
 */
#include <cstdio>
using namespace std;

double a, b, e, m = 1e8;
int c, d, x, y;

int main() {
    scanf("%lf%lf%d%d%lf", &a, &b, &c, &d, &e);
    while (~c && ~d) {
        double k = (a * c + b * d) / (c + d);
        if (k < e) { --c; continue; }
        if (m - k > 1e-8) x = c, y = d, m = k;
        --d;
    }
    printf("%d %d", x, y);
    return 0;
}