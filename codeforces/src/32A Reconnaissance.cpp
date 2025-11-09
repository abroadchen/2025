//
// Created by Psy.C on 2025/9/21.
//

#include <algorithm>
#include <cstdio>
using namespace std;

int main() {

    long n(0), d(0); scanf("%ld %ld", &n, &d);// 读取点的数量n和距离阈值d
    long* height = new long[n];// 动态分配数组存储点的高度值

    for (int i = 0; i < n; ++i) scanf("%ld", &height[i]);
    sort(height, height + n);

    long total(0);// 记录满足条件的点对总数
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {// j > i确保不重复计算
            if (height[j] <= height[i] + d) ++total;// 如果点j的高度不超过点i高度加d
            else break;// 由于已排序，后续点都不满足条件，可以提前退出
        }
    // 输出结果：乘以2是因为每对点可以有两种顺序
    printf("%ld\n", 2 * total);
    delete[] height;// 释放动态分配的内存
    return 0;
}