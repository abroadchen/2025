//
// Created by Psy.C on 2025/11/16.
//
/*
*a: 玩家1的能力值
b: 玩家2的能力值
n: 初始石头数量
 *
*t: 回合计数器
游戏循环，直到石头被取完(n == 0)：
回合数加1
如果是奇数回合(t & 1为真，即玩家1的回合)：
玩家1取走gcd(a, n)个石头
如果是偶数回合(t & 1为假，即玩家2的回合)：
玩家2取走gcd(b, n)个石头
 *
*如果总回合数是奇数，说明玩家1取走了最后一堆石头，输出"0"
如果总回合数是偶数，说明玩家2取走了最后一堆石头，输出"1"
 *
 *O(log(min(a,b)) × 回合数)，因为每次GCD计算需要O(log)时间
 */
#include <cstdio>
using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    int a, b, n;
    while (~scanf("%d%d%d", &a, &b, &n)) {
        int t(0);
        while (n != 0) {
            ++t;
            if (t & 1) n -= gcd(a, n);
            else n -= gcd(b, n);
        }
        if (t & 1) printf("0\n");
        else printf("1\n");
    }
    return 0;
}