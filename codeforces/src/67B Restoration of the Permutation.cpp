//
// Created by Psy.C on 2025/10/31.
//
/*
* n: 序列长度
// k: 参数k
// v[N]: 计数数组，用于跟踪可用位置
// p[N]: 结果数组，存储输出序列
// i, j: 循环变量
 *
*  // 寻找第一个v[j]为0的位置（即可用位置）
        // 从j=1开始递增，直到找到v[j]==0
 *将找到的位置j标记为已使用（减少计数）
 *将当前位置j保存到结果数组p中
*从(j-k)位置开始向前，对范围内的位置进行减一操作
        // 这会影响当前位置前面k个位置的计数值
 *输出结果数组p中的所有元素
 *
 *
 *时间复杂度：O(n²)，因为对于每个元素都需要线性时间来查找合适的位置
 *空间复杂度：O(n)，使用了线性额外空间存储数组v和p
 *
 */
#include <iostream>
using namespace std;

const int N = 1005;
int n, k, v[N], p[N], i, j;


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for (i = 1; i <= n; ++i) cin >> v[i];
    for (i = 0; i < n; ++i) {
        for (j = 1; v[j]; ++j);
        v[j]--;
        p[i] = j;
        for (j -= k; j >= 1; --j) v[j]--;
    }
    for (i = 0; i < n; ++i) cout << p[i] << " ";
    return 0;
}