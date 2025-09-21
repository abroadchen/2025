//
// Created by Psy.C on 2025/9/21.
//

#include <cstdio>
#include <cstdlib>
using namespace std;

int main() {

    int n; scanf("%d\n",&n);
    int* heights = new int[n];
    for (int i = 0; i < n; ++i) scanf("%d",&heights[i]);
    // 初始化：计算首尾元素的差值（环形数组特性）
    int diff(abs(heights[0]-heights[n - 1])), index(n - 1);// 最小差值对应的索引
    for (int i = 0; i < n - 1; ++i) {// 遍历所有相邻元素对（包括环形连接）
        if (abs(heights[i] - heights[i + 1]) < diff) {
            diff = abs(heights[i] - heights[i + 1]);
            index = i;
        }
    }
    printf("%d %d\n",1 + index, 1 + (index + 1) % n);//通过模运算 (index + 1) % n 实现环形连接
    return 0;
}