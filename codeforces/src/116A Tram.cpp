//
// Created by Psy.C on 2025/11/15.
//
/*
*时间复杂度：O(n) - 只需一次遍历
空间复杂度：O(1) - 只使用常数额外空间
核心思想：维护当前状态和历史最大值
 */
#include <cstdio>
using namespace std;

int main() {
    int n, a, b, c(0), m(0);
    scanf("%d", &n);
    while(n--) {
        scanf("%d%d", &a, &b);
        c -= a;
        c += b;
        if (c > m) m = c;
    }
    printf("%d\n", m);
    return 0;
}