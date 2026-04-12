//
// Created by Psy.C on 2026/4/11.
//
/**
scanf("%d%c%d", &a, &s, &ta);: 读取第一个时间格式，如"2:30"
%d: 读取数字到变量a（小时）
%c: 读取字符到变量s（冒号）
%d: 读取数字到变量ta（分钟）
scanf("%d%c%d", &b, &s, &tb);: 读取第二个时间格式
%d: 读取数字到变量b（小时）
%c: 读取字符到变量s（冒号）
%d: 读取数字到变量tb（分钟）
scanf("%s", str);: 读取时间字符串到str数组

将字符串时间"HH:MM"转换为从00:00开始的分钟数
str[0]-'0': 小时十位数
str[1]-'0': 小时个位数
(str[0]-'0')*10+(str[1]-'0'): 总小时数
(...)*60: 转换为分钟
+(str[3]-'0')*10+(str[4]-'0'): 加上分钟数
ed = st + ta: 结束时间为起始时间+持续时间
l = 300: 设置左边界为300分钟（5:00 AM）
r = 24*60 - 1: 设置右边界为1439分钟（23:59 PM）

i + tb > st: 第二个事件的结束时间大于第一个事件的开始时间
i < ed: 第二个事件的开始时间小于第一个事件的结束时间
这个条件检查两个时间段是否有交集
ans++: 如果有交集，计数器加1
 */
#include <bits/stdc++.h>
using namespace std;

int a, ta, b, tb;
char str[10], s;
int main() {
    scanf("%d%c%d", &a, &s, &ta);
    scanf("%d%c%d", &b, &s, &tb); scanf("%s", str);
    int st = ((str[0]-'0')*10+(str[1]-'0'))*60+(str[3]-'0')*10+(str[4]-'0'),
    ed = st + ta, l = 300, r = 24*60 - 1, ans = 0;
    for (int i = l; i <= r; i += b)
        if (i + tb > st && i < ed)
            ans++;
    cout << ans << '\n';
    return 0;
}