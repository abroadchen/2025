//
// Created by Psy.C on 2025/11/18.
//
/*
*n: 数组元素个数
i: 循环变量
a[N]: 存储输入数据的数组
p: 前一个不同数值
t(0): 计数器，初始化为0
j: 内层循环变量
s: 当前相同数字的个数
 *
*外层循环，按相同数字的组进行遍历
注意：循环增量是 i = j 而不是 i++，j在内层循环中确定
*内层循环：找到从位置i开始所有相同数字的末尾位置
j最终指向第一个不同于a[i]的元素位置
循环结束后，从i到j-1都是相同的数字a[i]
 *
*检查当前数字a[i]与前一个不同数字p的差值
如果差值大于1，说明不连续
*计算当前相同数字的个数：s = j - i
如果当前个数s大于计数器t：
更新p为当前数字a[i]
更新t为s - t（当前个数减去之前的计数）
 *如果当前个数s不大于t，则从t中减去s
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 102400;
int n, i, a[N], p, t(0), j, s;

int main() {
    scanf("%d",&n);
    for (i = 0; i < n; ++i) scanf("%d",&a[i]);
    sort(a, a + n);
    p = *a;//将p初始化为数组第一个元素的值（最小值）
    for (i = 0; i < n; i = j) {
        for (j = i + 1; a[j] == a[i]; ++j);
        if (a[i] - p > 1) return puts("NO"), 0;
        if ((s = j - i) > t) p = a[i], t = s - t;
        else t -= s;
    }
    puts(t ? "NO" : "YES");
    return 0;
}