//
// Created by Psy.C on 2026/1/7.
//
/**
 *u, v：目标坐标的x和y值
 *x = 0, y = 0：累积位移的x和y值
 *存储路径上每个点的坐标，g[i][0]为x坐标，g[i][1]为y坐标
 *s[N]：存储输入的路径字符串
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
#define inf 2e9
using namespace std;


int main() {
    fast;
    int u, v, x = 0, y = 0, g[N][2], i; char s[N]; cin >> u >> v >> s;
    for (i = 0; s[i]; ++i) {
        if (s[i] == 'U') y++;
        if (s[i] == 'D') y--;
        if (s[i] == 'L') x--;
        if (s[i] == 'R') x++;
        g[i+1][0] = x; g[i+1][1] = y;//保存当前累积位置到g数组，i+1位置存储第i步后的坐标
    }
    const int n = i;
    int k = inf;
    if (u == 0 && v == 0) {//目标点是否就是起点(0,0)
        cout << "Yes\n";
        return 0;
    }
    for (i = 0; i <= n; ++i) {//遍历路径上的每个位置（包括起点）
        const int dx = u - g[i][0], dy = v - g[i][1];//目标点x坐标与当前位置x坐标的差值
        if (x) k = dx / x;//x方向有净位移 计算需要重复多少次路径循环才能在x方向上到达目标
        else if (y) k = dy / y;
        else k = 1;//x和y都为0（路径循环后回到原点）
        if (k >= 0 && x * k == dx && y * k == dy) break;//x位移是否等于所需x位移
        //如果条件满足，说明可以通过k次循环到达目标，跳出循环
    }
    cout << (i <= n ? "Yes\n" : "No\n");
    return 0;
}