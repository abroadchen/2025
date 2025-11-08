//
// Created by Psy.C on 2025/10/15.
//
/*
*h: 高度
w: 宽度
t: 临时变量
p: 初始值为1的变量，用于表示2的幂次
a, b: 最终结果变量
 *
*每次循环结束后将p左移一位（相当于p *= 2）
这样p依次取值为1, 2, 4, 8, 16, ..., 2^29
 *
*更新最优解：
如果当前面积p*t更大，或者面积相等但新的a值更小，则更新a和b
这确保找到面积最大，且在面积相同时a最小的解
 *
*约束条件：

矩形的一边长度为2的幂次（p）
矩形的另一边满足某种比例关系（不超过5*p/4）
矩形必须能在给定的h×w区域内放置
算法思路：

遍历所有可能的2的幂次作为一边长度
对于每个可能的长度，计算另一边的最大可能长度
在所有可行解中选择面积最大的，如果面积相同则选择特定条件下更优的
 */
#include <cstdio>
#define min(a,b) (((a)<(b))?(a):(b))
using namespace std;

typedef long long ll;
ll h, w, t, p(1), a, b;

int main() {

    register int i; scanf("%lld%lld", &h, &w);

    for (i = 0; i < 30; ++i, p <<= 1) {
        if (p <= h && 4 * p <= 5 * w) {
            t = min(w, 5 * p / 4);
            if (p * t > a * b || (p * t == a * b && a < p))
                a = p, b = t;
        }
        if (p <= w && 4 * p <= 5 * h) {
            t = min(h, 5 * p / 4);
            if (p * t > a * b || (p * t == a * b && a < t))
                a = t, b = p;
        }
    }
    printf("%lld %lld\n", a, b);
    return 0;
}