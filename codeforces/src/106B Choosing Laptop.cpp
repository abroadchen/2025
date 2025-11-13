//
// Created by Psy.C on 2025/11/13.
//
/*
*定义常量：N=110（数组大小），M=1100（标记值）
声明变量：
n：元素个数
idx：最优元素的索引
k：最小优先级值，初始化为1010
 *
*第一轮比较：
对于每对元素(i,j)，其中i<j
如果元素i的s、r、h都小于元素j对应的值
则将元素i的优先级p设置为M（标记为无效）
*第二轮比较：
对于每对元素(i,j)，其中i>j
如果元素i的s、r、h都小于元素j对应的值
则将元素i的优先级p设置为M（标记为无效）
*寻找优先级最小的有效元素：
遍历所有元素
如果元素的优先级小于当前最小值k
更新最小值k和对应索引idx
 */
#include <iostream>
using namespace std;

const int N = 110, M = 1100;
int n, idx, k = 1010;
struct Node { int s, r, h, p; } a[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> a[i].s >> a[i].r >> a[i].h >> a[i].p;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i].s < a[j].s) if (a[i].r < a[j].r) if (a[i].h < a[j].h) {
                a[i].p = M;
            }
        }
    }
    for (int i = n; i > 1; --i) {
        for (int j = i - 1; j >= 1; --j) {
            if (a[i].s < a[j].s) if (a[i].r < a[j].r) if (a[i].h < a[j].h) {
                a[i].p = M;
            }
        }
    }
    for (int i = 1; i <= n; ++i) if (a[i].p < k) {
        k = a[i].p; idx = i;
    }
    cout << idx;
    return 0;
}