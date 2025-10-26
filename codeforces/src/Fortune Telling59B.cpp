//
// Created by Psy.C on 2025/10/26.
//
/*
*t(0): 临时存储当前读取的数字
ans(0): 所有数字的总和
o(101): 最小奇数，初始化为101（题目中数字范围的上界）
tot(0): 奇数的个数统计
 *
*循环n次读取数字：
使用scanf读取下一个整数存入t
将t加到总和ans中
判断t是否为奇数（t % 2 == 1）
如果是奇数：
奇数计数器tot加1
如果t比当前记录的最小奇数o更小，则更新o为t
 *
 *如果最小奇数仍然是初始值101（说明没有读取到任何奇数），输出"0"
*否则如果奇数个数为偶数个，则从总和中减去最小奇数后输出
（因为偶数个奇数相加为偶数，需要去掉一个奇数才能使总和为奇数）
*否则如果奇数个数为奇数个，则直接输出总和
（因为奇数个奇数相加为奇数，总和本身就是奇数）
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {

    int n(0); scanf("%d",&n);
    int t(0), ans(0), o(101), tot(0);
    for (int i = 0; i < n; ++i) {
        scanf("%d",&t);
        ans += t;
        if (t % 2 == 1) {
            ++tot;
            if (t < o) o = t;
        }
    }
    if (o > 100) puts("0");
    else if (tot % 2 == 0) printf("%d\n", ans - o);
    else if (tot % 2 == 1) printf("%d\n", ans);
    return 0;
}