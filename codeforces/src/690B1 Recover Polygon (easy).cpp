//
// Created by Psy.C on 2026/4/16.
//
/**
dx[] = {1,1,-1,-1}：方向数组，表示四个对角线方向的x坐标偏移量
dy[] = {-1,1,-1,1}：方向数组，表示四个对角线方向的y坐标偏移量
这四个方向分别代表左下(1,-1)、右下(1,1)、左上(-1,-1)、右上(-1,1)
scanf("%1d", &s[i][j]);：每次读取一个数字字符并转换为整数存储到s[i][j]
%1d表示只读取一位数字

遍历网格中的每一个位置(i,j)
cnt是在内层循环中声明的计数器
如果当前位置的值为0，则跳过这个位置继续检查下一个位置
将计数器cnt初始化为0
循环k=0到3，遍历四个对角线方向
i+dx[k]和j+dy[k]计算出对角线相邻位置的坐标
if (s[i+dx[k]][j+dy[k]])检查对角线相邻位置是否有值为1
如果相邻位置的值为真（即为1），则计数器cnt加1
比较当前格子的值与它周围对角线方向上1的个数
如果不相等，则输出"No"并结束程序，返回值为0
 */
#include <bits/stdc++.h>
using namespace std;

int n, s[51][51], dx[] = {1,1,-1,-1}, dy[] = {-1,1,-1,1};
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%1d", &s[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1, cnt; j <= n; j++) {
            if (s[i][j] == 0) continue;
            cnt = 0;
            for (int k = 0; k < 4; k++)
                if (s[i+dx[k]][j+dy[k]])
                    cnt++;
            if (s[i][j] != cnt)
                return cout << "No\n", 0;
        }
    cout << "Yes\n";
    return 0;
}