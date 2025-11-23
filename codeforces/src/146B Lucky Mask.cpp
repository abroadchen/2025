//
// Created by Psy.C on 2025/11/21.
//

#include <cstdio>
using namespace std;

//提取数字中只包含4和7的位，组成新数字
int func(int x) {
    int res = 0, mul = 1;//mul:位权(1,10,100...)
    while (x > 0) {// 从右到左处理x的每一位
        if (x % 10 == 4 || x % 10 == 7) {//如果当前位是4或7
            res += mul * (x % 10);//将这一位加入结果中
            mul *= 10;//位权乘以10，为下一位做准备
        }
        x /= 10;//去掉x的最后一位
    }
    return res;
}

int main() {
    int a, b; scanf("%d %d", &a, &b);
    int ans(a + 1);//从a+1开始寻找答案
    while (func(ans) != b) ++ans;//循环直到找到满足条件的数字
    printf("%d\n", ans);
    return 0;
}