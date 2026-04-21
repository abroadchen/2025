//
// Created by Psy.C on 2026/4/20.
//
/**
x: 棋盘列（a-h）
y: 棋盘行（1-8）
x == 'a' || x == 'h': 检查是否在最左列或最右列
y == '1' || y == '8': 检查是否在最底行或最顶行
flag: 记录边界条件的数量
if (flag == 0) return 8;    // 中央位置：8步
if (flag == 1) return 5;    // 边缘位置：5步
return 3;                   // 角落位置：3步

1. 中央位置 (flag == 0)
不在边缘也不在角落
所有8个方向都可达
返回8
2. 边缘位置 (flag == 1)
在行边界或列边界上（但不是角落）
有3个方向被阻挡
剩余5个方向可达
返回5
3. 角落位置 (flag == 2)
同时在行边界和列边界（角落）
有5个方向被阻挡
剩余3个方向可达
返回3

读入棋盘坐标（如 "e4"）
调用get函数计算骑士可移动步数
O(1): 常数时间计算
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[2];
int get(char x, char y) {
    int flag = 0;
    if (x == 'a' || x == 'h') flag++;
    if (y == '1' || y == '8') flag++;
    if (flag == 0) return 8;
    if (flag == 1) return 5;
    return 3;
}

int main() {
    fast;
    scanf("%s", s);
    cout << get(s[0], s[1]);
    return 0;
}