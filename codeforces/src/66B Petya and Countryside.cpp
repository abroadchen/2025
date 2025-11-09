//
// Created by Psy.C on 2025/10/30.
//
/*
*n：将存储元素的数量
b：临时计数器，用于连续序列计数，初始化为0
res：存储找到的最大结果，初始化为0
 *
*h：将存储高度值
s：将存储每个位置的得分
*读取n个高度值到数组h中
将数组s的所有元素初始化为0
 *
*从左到右的第一遍扫描：
对于每个位置（从索引1开始），检查当前高度是否大于等于前一个高度
如果是，则递增b并将其加到s[i]上（计算递增序列长度）
如果否，则将b重置为0
 *
*从右到左的第二遍扫描：
对于每个位置（从倒数第二个开始），检查当前高度是否大于等于下一个高度
如果是，则递增b并将其加到s[i]上（计算递减序列长度）
如果否，则将b重置为0
 *
 *在数组s中找到最大值并存储在res中
 *输出结果（加1是为了计入基准元素本身）
 *
 */
#include <cstdio>
using namespace std;

int n, b(0), res(0);

int main() {
    scanf("%d", &n);
    int* h = new int[n], *s = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", h + i);
        s[i] = 0;
    }

    for (int i = 1; i < n; ++i) {
        if (h[i - 1] <= h[i]) s[i] += ++b;
        else b = 0;
    }
    b = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (h[i] >= h[i + 1]) s[i] += ++b;
        else b = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] > res) res = s[i];
    }
    printf("%d\n", res + 1);
    return 0;
}