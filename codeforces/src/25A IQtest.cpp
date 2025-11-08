//
// Created by Psy.C on 2025/9/19.
//
/*
*读取前3个数字，并将它们模2（转换为奇偶性）
0表示偶数，1表示奇数
 *
 *
*初始化变量：target(目标奇偶性)、index(目标索引)、done(是否完成)
逻辑判断：
如果前两个数字奇偶性相同(temp[0] == temp[1])：
target设为与前两个数字相反的奇偶性(1 - temp[0])
如果第三个数字正好是target，则index=2，标记完成
如果前两个数字奇偶性不同：
标记完成
如果第三个数字与第一个相同，则异常索引是1
否则异常索引是0
 *
 *
*如果前面没有找到答案(done=0)，继续处理剩余数字
读取第4个及以后的数字
如果数字的奇偶性等于target，则找到目标索引
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {
    int n; scanf("%d",&n);
    int temp[3] = {0};
    for (int i = 0; i < 3; ++i) {
        scanf("%d", temp + i);
        temp[i] %= 2;
    }

    int target = 0, index = 0;
    bool done = 0;
    if (temp[0] == temp[1]) {
        target = 1 - temp[0];
        if (temp[2] == target) {
            index = 2;
            done = 1;
        }
    } else {
        done = 1;
        if (temp[2] == temp[0]) index = 1;
        else index = 0;
    }

    int current = 0;
    for (int i = 3; i < n && !done; ++i) {
        scanf("%d", &current);
        if (current % 2 == target) {
            index = i;
            break;
        }
    }
    printf("%d\n", index + 1);

    return 0;
}