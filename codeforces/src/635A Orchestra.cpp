//
// Created by Psy.C on 2026/3/31.
//
/**
r, c：矩阵的行数和列数
n：障碍物数量
k：矩形区域内最少需要的障碍物数量
mp[12][12]：二维数组，存储地图状态（1表示有障碍物，0表示无障碍物）
初始化计数器g为0：记录满足条件的矩形数量
四重嵌套循环：枚举所有可能的矩形区域，其中：
(x1, y1)：矩形左上角坐标
(x2, y2)：矩形右下角坐标
确保 x2 >= x1 和 y2 >= y1
初始化k1为0：k1用来统计当前矩形内的障碍物数量
双重循环遍历矩形内部：计算从(x1,y1)到(x2,y2)范围内所有格子的障碍物总和
条件判断：如果当前矩形内的障碍物数量大于等于要求的k值，则将结果计数器g加1
时间复杂度为O(r²c²rc)=O(r³c³)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int r, c, n, k, mp[12][12];
int main() {
    fast;
    cin >> r >> c >> n >> k;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y; mp[x][y] = 1;
    }
    int g = 0;
    for (int x1 = 1; x1 <= r; ++x1)
        for (int y1 = 1; y1 <= c; ++y1)
            for (int x2 = x1; x2 <= r; ++x2)
                for (int y2 = y1, k1; y2 <= c; ++y2) {
                    k1 = 0;
                    for (int b = x1; b <= x2; ++b)
                        for (int e = y1; e <= y2; ++e)
                            k1 += mp[b][e];
                    if (k1 >= k) g++;
                }
    cout << g << '\n';
    return 0;
}