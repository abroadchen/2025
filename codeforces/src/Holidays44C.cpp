//
// Created by Psy.C on 2025/9/26.
//
/*
*cur：当前处理的位置，初始化为0
d：发现问题的位置，初始化为-1（表示未发现问题）
t：时间或计数器，初始化为1
 *
*条件判断：如果当前处理位置的下一个位置(cur+1)小于区间起始位置a
这意味着在cur+1和a之间存在空隙
*发现问题：设置问题位置d为cur+1（空隙的开始）
设置时间t为0
使用break跳出循环
*否则如果区间起始位置a小于当前处理位置的下一个位置(cur+1)
这意味着区间a与已处理区域有重叠
*设置问题位置d为a
时间计数器t加1
如果b > a，则跳出循环
 *更新当前处理位置为区间的结束位置b
 *
*如果未发现问题(d仍为-1)且当前处理位置小于总长度n
这意味着还有未处理的区域
设置问题位置d为cur+1
设置时间t为0


如果仍未发现问题(d仍为-1)，输出"OK"
puts函数输出字符串并自动换行
否则输出发现问题的位置d和时间t
 */
#include <cstdio>
using namespace std;

int main() {

    long n, m; scanf("%ld %ld", &n, &m);
    long cur(0), d(-1), t(1);

    for (long i = 0; i < m; ++i) {
        long a, b; scanf("%ld %ld", &a, &b);
        if (cur + 1 < a) {
            d = cur + 1;
            t = 0;
            break;
        } else if (a < cur + 1) {
            d = a;
            ++t;
            if (b > a) break;
        }
        cur = b;
    }

    if (d < 0 && cur < n) {
        d = cur + 1;
        t = 0;
    }
    if (d < 0) puts("OK");
    else printf("%ld %ld\n", d, t);
    return 0;
}