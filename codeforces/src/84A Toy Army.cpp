//
// Created by Psy.C on 2025/11/7.
//
/*
 *3 * n / 2 等价于 floor(3n/2)（整数除法）
*时间复杂度：O(1) - 常数时间
空间复杂度：O(1) - 常数空间
 */
#include <cstdio>
using namespace std;

int main() {
    int n; scanf("%d",&n);
    printf("%d\n",3 * n / 2);
    return 0;
}