//
// Created by Psy.C on 2025/10/17.
//
/*
 *创建一个大小为 n 的向量 p，初始化为0，用来标记已访问的位置。
 *由于我们从位置0开始，所以将位置0标记为已访问。
 *
*模拟长度为1, 2, 3, ..., 直到2*n的移动：

将移动长度 i 加到当前位置
使用模运算 n 来处理循环数组的边界情况
将新到达的位置标记为已访问
进行2n次移动的原因是，在最多2n步之后，模式要么覆盖了所有位置，要么进入了不能覆盖所有位置的循环。
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    int n; scanf("%d\n",&n);
    vector<int> p(n, 0); p[0] = 1;
    int cur(0);
    for (int i = 1; i <= 2 * n; ++i) {
        cur += i;
        cur %= n;
        p[cur] = 1;
    }
    bool f(1);
    for (int i = 0; i < n; ++i) {
        if (p[i] == 0) {
            f = 0;
            break;
        }
    }
    puts(f ? "YES" : "NO");
    return 0;
}