//
// Created by Psy.C on 2025/9/21.
//
/*
 *
* d < 1: 日期不能小于1
    // d > day[m] + (m == 2 && y % 4 == 0): 日期不能超过该月天数，如果是2月且闰年则加1天
    // m < 1 || m > 12: 月份必须在1-12之间
    // y < 1 || y > 99: 年份必须在1-99之间
 *
* 满18岁的条件：
    // 1. 年龄差大于18岁
    // 2. 年龄差等于18岁但月份更早
    // 3. 年龄差等于18岁且月份相同但日期不晚于当前日期
 *
 *
 */

#include <cstdio>
using namespace std;
int dd, mm, yy, bd, bm, by;// 存储当前日期和出生日期的变量
int day[20] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool check(int d, int m, int y) {
    if (d < 1 || d > day[m] + (m == 2 && y % 4 == 0) || m < 1 || m > 12 || y < 1 || y > 99) return false;
    return (yy - y > 18 || (yy - y == 18 && m < mm) || (d <= dd && m == mm && yy - y == 18));
}


int main() {
    scanf("%d.%d.%d", &dd, &mm, &yy); scanf("%d.%d.%d", &bd, &bm, &by);
    if (check(bd, bm, by) || check(bd, by, bm) || check(bm, bd, by) ||
        check(bm, by, bd) || check(by, bd, bm) || check(by, bm, bd))
        printf("YES");
    else
        printf("NO");

    return 0;
}