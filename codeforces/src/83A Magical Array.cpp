//
// Created by Psy.C on 2025/11/7.
//
/*
*n 表示数字的总个数
cur 表示当前读取的数字
prev 表示前一个数字 然后读取n的值。
 *读取第一个数字并存储在prev中
*tot 表示总的结果值，初始化为0
cnt 表示当前连续相同数字的计数，初始化为1（因为已经读取了第一个数字）
 *将n减1，因为已经读取了一个数字
 *循环处理剩余的n-1个数字
 *读取当前数字
 *如果当前数字等于前一个数字，增加连续计数cnt
*如果当前数字不等于前一个数字，说明连续序列结束：

将当前连续序列的贡献cnt * (cnt + 1) / 2加到总结果中
重置连续计数cnt为1，开始新的连续序列
 *更新prev为当前数字，为下一次比较做准备
 *处理最后一段连续序列的贡献（循环结束后还有一段未处理的连续序列）
 *cnt * (cnt + 1) / 2 就是计算连续相同元素能够组成的所有连续子序列的总数
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    int n, cur, prev; scanf("%d",&n);
    scanf("%d",&prev);
    ll tot(0), cnt(1);
    --n;
    while (n--) {
        scanf("%d",&cur);
        if (cur == prev) ++cnt;
        else {
            tot += cnt * (cnt + 1) / 2;
            cnt = 1;
        }
        prev = cur;
    }
    tot += cnt * (cnt + 1) / 2;
    printf("%lld\n", tot);
    return 0;
}