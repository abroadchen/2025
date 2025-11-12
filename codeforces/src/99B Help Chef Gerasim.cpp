//
// Created by Psy.C on 2025/11/12.
//
/*
*n：杯子数量
i：循环变量
a[N]：存储每个杯子的水量
cnt：计数器，初始为0
sum：总水量，初始为0
t：目标水量（平均值）
q2, q1：记录水量超过和低于平均值的杯子索引
 *
*循环读取每个杯子的水量：
读取第i个杯子的水量到a[i]
检查是否所有杯子水量都相同：
如果当前杯子水量等于前一个杯子水量，cnt递增
否则（水量不同），将cnt设为负无穷（标记为不全相同）
累加总水量到sum
 *
 *
*遍历所有杯子，找出水量不等于平均值的杯子：
如果杯子水量不等于平均值：
cnt计数器递增
将该杯子水量加入sum
记录该杯子索引：
如果水量大于平均值，记录到q2
如果水量小于平均值，记录到q1
 *
 *
*如果恰好有两个杯子水量不等于平均值：
检查这两个杯子的总水量是否等于两倍平均值（即可以平衡）
如果可以平衡，输出转移方案：
转移量：abs(a[q2]-a[q1])/2
从杯子#(q1+1)到杯子#(q2+1)（索引从1开始编号）
 *
 */
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 1000, inf = 1e6;

int main() {
    int n, i, a[N], cnt(0), sum(0), t, q2, q1;
    scanf("%d",&n);
    if (n == 1) { printf("Exemplary pages.\n"); return 0;}
    for (i = 0; i < n; ++i) {
        scanf("%d",&a[i]);
        if (i != 0 && a[i] == a[i - 1]) cnt++;
        else if (i != 0) cnt = -inf;
        sum += a[i];
    }
    if (cnt > 0) { printf("Exemplary pages.\n"); return 0; }//如果所有杯子水量都相同
    //如果总水量不能被杯子数整除（无法平均分配）
    if (sum % n != 0) { printf("Unrecoverable configuration.\n"); return 0; }
    t = sum / n; sum = 0; cnt = 0;
    for (i = 0; i < n; ++i) {
        if (a[i] != t) {
            cnt++; sum += a[i];
            if (a[i] > t) q2 = i;
            else q1 = i;
        }
    }
    if (cnt == 2) {
        if (sum / 2 == t) {
            printf("%d ml. from cup #%d to cup #%d.\n",
                abs(a[q2]-a[q1])/2, q1+1,q2+1);
            return 0;
        }
    }
    printf("Unrecoverable configuration.\n");
    return 0;
}