//
// Created by Psy.C on 2025/10/15.
//
/*
*循环n次读取输入：
t：临时变量存储当前读取的值
读取一个数值t
将c[t]计数加1（统计值为t的元素个数）
 *
*对计数数组c进行排序（从小到大）
输出排序后第2小和第3小的计数值之和
 *
 *时间复杂度：O(n) 空间复杂度：O(1)
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    long c[4] = {0}, n; scanf("%ld", &n);
    for (long i = 0; i < n; ++i) {
        int t; scanf("%ld", &t);
        ++c[t];
    }
    sort(c, c + 4);
    printf("%ld\n", c[1] + c[2]);
    return 0;
}