//
// Created by Psy.C on 2026/4/23.
//
/**
读入时间格式t（12或24）
读入格式为 "HH:MM" 的时间
如果分钟大于59，取个位数（即对10取模）
如果是12小时制：
如果小时大于12：
如果h不能被10整除，取个位数
如果h能被10整除，设为10
如果小时小于等于0，设为1
如果是24小时制：
如果小时大于23：
如果h不能被10整除，取个位数
如果h能被10整除，设为10
如果小时小于0，设为0
 */
#include <bits/stdc++.h>
using namespace std;

int t, m, h;
int main() {
    scanf("%d", &t);
    scanf("%d:%d", &h, &m);
    if (m < 0) m++;
    if (m > 59) m %= 10;
    if (t == 12) {
        if (h > 12) {
            if (h%10) h %= 10;
            else h = 10;
        }
        if (h <= 0) h = 1;
    } else {
        if (h > 23) {
            if (h%10) h %= 10;
            else h = 10;
        }
        if (h < 0) h = 0;
    }
    printf("%02d:%02d\n", h, m);
    return 0;
}