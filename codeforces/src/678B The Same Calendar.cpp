//
// Created by Psy.C on 2026/4/14.
//
/**
普通闰年：能被4整除但不能被100整除
世纪闰年：能被400整除
满足以上任一条件都是闰年

d = 0: 累积的日期偏移量（相对于起始年的同一天）
y = n: 保存原始年份

if (leap(n)) d += 2; else d++;:
如果当前年n是闰年，日期偏移量+2（因为闰年多一天，星期会向后移2天）
否则日期偏移量+1
d %= 7;: 日期偏移量对7取模（一周7天）
n++;: 年份+1
if (d == 0 && leap(y) == leap(n)):
d == 0: 日期偏移量为0，意味着星期回到了原来的状态
leap(y) == leap(n): 当前年份和原始年份同为闰年或同为平年
满足这两个条件时，同一天的星期数相同

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool leap(int y) {
    if ((y%4 == 0 && y%100 != 0) || y%400 == 0) return true;
    return false;
}

int n;
int main() {
    fast;
    cin >> n;
    int d = 0, y = n;
    while (true) {
        if (leap(n)) d += 2; else d++;
        d %= 7; n++;
        if (d == 0 && leap(y) == leap(n)) {
            cout << n << '\n';
            break;
        }
    }
    return 0;
}